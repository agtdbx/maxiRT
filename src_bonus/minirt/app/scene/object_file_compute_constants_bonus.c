/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_file_compute_constants_bonus.c              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auguste <auguste@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 19:51:32 by aderouba          #+#    #+#             */
/*   Updated: 2024/03/17 14:38:55 by auguste          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt/app/scene/scene_bonus.h"

#include <math.h>
#include <stdio.h>

#include "minirt/app/utils/geometry/geometry_bonus.h"

static void	compute_objf_vertices(
				t_object_file *objf);
static void	compute_objf_triangles(
				t_object_file *objf);
static void	compute_objf_triangle_pixel_pos_constants(
				t_object_triangle *triangle,
				float ax, float ay,
				float bx, float by,
				float cx, float cy,
				int pixel_pos_base);
static void	compute_objf_bounding_box(
				t_object_file *objf);
static void	calculate_bounding_box_bounds(
				t_object_file *objf,
				float	bounds_x[2],
				float	bounds_y[2],
				float	bounds_z[2]);
static void	set_min_max(
				float *nb,
				float bounds[2]);

#include <stdio.h>
/**
 * Compute constants from cube properties to facilitate further calculations
 * @param[out] cube
 */
void	object_file_compute_constants(
			t_object_file *objf)
{
	printf("OBJ{vertices : %i, triangles : %i}\n",
			objf->nb_vertices, objf->nb_triangles);

	vec3_cross(&objf->x_axis, &objf->y_axis, &objf->z_axis);
	vec3_normalize(&objf->x_axis);
	vec3_normalize(&objf->y_axis);
	vec3_normalize(&objf->z_axis);

	// Compute all vertices
	compute_objf_vertices(objf);

	// Compute all triangles
	compute_objf_triangles(objf);

	// Compute bounding box
	compute_objf_bounding_box(objf);
}


static void	compute_objf_vertices(
				t_object_file *objf)
{
	int	i;

	i = 0;
	while (i < objf->nb_vertices)
	{
		objf->real_vertices[i] = objf->vertices[i];
		// Scale points
		vec3_scale(&objf->real_vertices[i], objf->size);
		// Rotate points along objf axis
		objf->real_vertices[i] = mat_product(&objf->x_axis, &objf->y_axis,
									&objf->z_axis, &objf->real_vertices[i]);
		// Move points along objf position
		vec3_add(&objf->real_vertices[i], &objf->pos);
		i++;
	}
}

static void	compute_objf_triangles(
				t_object_file *objf)
{
	int	i;

	i = 0;
	while (i < objf->nb_triangles)
	{
		t_object_triangle *triangle = &objf->triangles[i];

		// Get points from real vertice
		triangle->point1 = objf->real_vertices[triangle->vertice_1];
		triangle->point2 = objf->real_vertices[triangle->vertice_2];
		triangle->point3 = objf->real_vertices[triangle->vertice_3];

		// Compute triangle constants
		vec3_substract_into(&triangle->edge1, &triangle->point2, &triangle->point1);
		vec3_substract_into(&triangle->edge2, &triangle->point3, &triangle->point1);
		triangle->normal.x = (triangle->edge1.y * triangle->edge2.z)
							- (triangle->edge1.z * triangle->edge2.y);
		triangle->normal.y = (triangle->edge1.z * triangle->edge2.x)
							- (triangle->edge1.x * triangle->edge2.z);
		triangle->normal.z = (triangle->edge1.x * triangle->edge2.y)
							- (triangle->edge1.y * triangle->edge2.x);
		vec3_normalize(&triangle->normal);

		// Compute pixel pos constants
		compute_objf_triangle_pixel_pos_constants(
			triangle,
			triangle->point1.x, triangle->point1.y,
			triangle->point2.x, triangle->point2.y,
			triangle->point3.x, triangle->point3.y,
			0);
		if (triangle->div_part == 0.0f)
		{
			compute_objf_triangle_pixel_pos_constants(
			triangle,
			triangle->point1.x, triangle->point1.z,
			triangle->point2.x, triangle->point2.z,
			triangle->point3.x, triangle->point3.z,
			1);
			if (triangle->div_part == 0.0f)
			{
				compute_objf_triangle_pixel_pos_constants(
				triangle,
				triangle->point1.z, triangle->point1.y,
				triangle->point2.z, triangle->point2.y,
				triangle->point3.z, triangle->point3.y,
				2);
				if (triangle->div_part == 0.0f)
					triangle->pixel_pos_base = -1;
			}
		}
		i++;
	}
}


static void	compute_objf_triangle_pixel_pos_constants(
				t_object_triangle *triangle,
				float ax, float ay,
				float bx, float by,
				float cx, float cy,
				int pixel_pos_base)
{
	float	ACy;

	triangle->BCy = by - cy;
	triangle->CBx = cx - bx;
	ACy = ay - cy;
	triangle->CAy = cy - ay;
	triangle->ACx = ax - cx;

	triangle->div_part = (triangle->BCy * triangle->ACx)
						+ (triangle->CBx * ACy);
	if (triangle->div_part != 0.0f)
	{
		triangle->pixel_pos_base = pixel_pos_base;
		triangle->div_part = 1.0f / triangle->div_part;
	}
}


static void	compute_objf_bounding_box(
				t_object_file *objf)
{
	float	bounds_x[2];
	float	bounds_y[2];
	float	bounds_z[2];
	t_cube	*cube;

	// Get mins and max
	calculate_bounding_box_bounds(objf, bounds_x, bounds_y, bounds_z);

	// Calculate cube info
	cube = &objf->bounding_box;

	cube->witdh = bounds_x[1] - bounds_x[0];
	cube->height = bounds_y[1] - bounds_y[0];
	cube->depth = bounds_z[1] - bounds_z[0];

	cube->pos.x = (bounds_x[1] + bounds_x[0]) / 2.0f;
	cube->pos.y = (bounds_y[1] + bounds_y[0]) / 2.0f;
	cube->pos.z = (bounds_z[1] + bounds_z[0]) / 2.0f;
	vec3_add(&cube->pos, &objf->pos);

	cube->x_axis = (t_vec3){1.0f, 0.0f, 0.0f};
	cube->y_axis = (t_vec3){0.0f, 1.0f, 0.0f};
	cube_compute_constants(cube);
}

static void	calculate_bounding_box_bounds(
				t_object_file *objf,
				float	bounds_x[2],
				float	bounds_y[2],
				float	bounds_z[2])
{
	int		i;
	t_vec3	point;

	i = 0;
	bounds_x[0] = 0;
	bounds_y[0] = 0;
	bounds_z[0] = 0;
	bounds_x[1] = 0;
	bounds_y[1] = 0;
	bounds_z[1] = 0;
	while (i < objf->nb_vertices)
	{
		point = objf->real_vertices[i];
		vec3_substract(&point, &objf->pos);
		set_min_max(&point.x, bounds_x);
		set_min_max(&point.y, bounds_y);
		set_min_max(&point.z, bounds_z);
		i++;
	}
}

static void	set_min_max(
				float *nb,
				float bounds[2])
{
	if (bounds[0] > *nb)
		bounds[0] = *nb;
	if (bounds[1] < *nb)
		bounds[1] = *nb;
}
