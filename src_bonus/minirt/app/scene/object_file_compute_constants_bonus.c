/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_file_compute_constants_bonus.c              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auguste <auguste@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 19:51:32 by aderouba          #+#    #+#             */
/*   Updated: 2024/03/17 20:08:42 by auguste          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt/app/scene/scene_bonus.h"

#include <math.h>

#include "minirt/app/utils/geometry/geometry_bonus.h"

static void	axis_checker(
				t_object_file *objf);
static void	compute_objf_vertices(
				t_object_file *objf);
static void	compute_objf_polygons(
				t_object_file *objf);
static void	compute_objf_triangle(
				t_object_file *objf,
				t_object_triangle *triangle);
static void	compute_objf_rectangle(
				t_object_file *objf,
				t_object_rectangle *rectangle);
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
	printf("OBJ{vertices : %i, polygons : %i}\n",
			objf->nb_vertices, objf->nb_polygons);

	axis_checker(objf);

	vec3_cross(&objf->x_axis, &objf->y_axis, &objf->z_axis);
	vec3_normalize(&objf->x_axis);
	vec3_normalize(&objf->y_axis);
	vec3_normalize(&objf->z_axis);

	// Compute all vertices
	compute_objf_vertices(objf);

	// Compute all polygons
	compute_objf_polygons(objf);

	// Compute bounding box
	compute_objf_bounding_box(objf);
}


static void	axis_checker(
				t_object_file *objf)
{
	if (vec3_dot(&objf->x_axis, &objf->y_axis) != 0.0f)
	{
		if (vec3_dot(&objf->x_axis, &objf->z_axis) != 0.0f)
			vec3_cross(&objf->y_axis, &objf->z_axis, &objf->x_axis);
		else
			vec3_cross(&objf->x_axis, &objf->z_axis, &objf->y_axis);
	}
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

static void	compute_objf_polygons(
				t_object_file *objf)
{
	int	i;

	i = 0;
	while (i < objf->nb_polygons)
	{
		if (objf->polygons[i].type == OBJF_TRIANGLE)
			compute_objf_triangle(objf, &objf->polygons[i].value.as_objf_triangle);
		else if (objf->polygons[i].type == OBJF_RECTANGLE)
			compute_objf_rectangle(objf, &objf->polygons[i].value.as_objf_rectangle);
		i++;
	}
}


static void	compute_objf_triangle(
				t_object_file *objf,
				t_object_triangle *triangle)
{

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
}


static void	compute_objf_rectangle(
				t_object_file *objf,
				t_object_rectangle *rectangle)
{
	t_vec3	p2_p1;
	t_vec3	p3_p1;

	// Get points from real vertice
	rectangle->point1 = objf->real_vertices[rectangle->vertice_1];
	rectangle->point2 = objf->real_vertices[rectangle->vertice_2];
	rectangle->point3 = objf->real_vertices[rectangle->vertice_3];
	rectangle->point4 = objf->real_vertices[rectangle->vertice_4];

	// Compute normal
	vec3_substract_into(&p2_p1, &rectangle->point2, &rectangle->point1);
	vec3_substract_into(&p3_p1, &rectangle->point3, &rectangle->point1);
	vec3_cross(&p2_p1, &p3_p1, &rectangle->normal);
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
