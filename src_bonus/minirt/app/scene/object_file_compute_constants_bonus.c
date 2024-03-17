/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_file_compute_constants_bonus.c              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auguste <auguste@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 19:51:32 by aderouba          #+#    #+#             */
/*   Updated: 2024/03/17 12:16:31 by auguste          ###   ########.fr       */
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
static void	compute_objf_bounding_box(
				t_object_file *objf);


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
	float	ACy;

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

		triangle->BCy = triangle->point2.y - triangle->point3.y;
		triangle->CBx = triangle->point3.x - triangle->point2.x;
		ACy = triangle->point1.y - triangle->point3.y;
		triangle->CAy = triangle->point3.y - triangle->point1.y;
		triangle->ACx = triangle->point1.x - triangle->point3.x;

		triangle->div_part = (triangle->BCy *triangle-> ACx)
							+ (triangle->CBx * ACy);
		if (triangle->div_part != 0.0f)
			triangle->div_part = 1.0f / triangle->div_part;
		i++;
	}
}


static void	compute_objf_bounding_box(
				t_object_file *objf)
{
	float	min_x;
	float	min_y;
	float	min_z;
	float	max_x;
	float	max_y;
	float	max_z;
	int		i;
	t_vec3	point;
	t_cube	*cube;

	// Get mins and max
	i = 0;
	min_x = 0;
	max_y = 0;
	min_z = 0;
	max_x = 0;
	min_y = 0;
	max_z = 0;
	while (i < objf->nb_vertices)
	{
		point = objf->real_vertices[i];
		vec3_substract(&point, &objf->pos);
		if (min_x > point.x)
			min_x = point.x;
		if (max_x < point.x)
			max_x = point.x;

		if (min_y > point.y)
			min_y = point.y;
		if (max_y < point.y)
			max_y = point.y;

		if (min_z > point.z)
			min_z = point.z;
		if (max_z < point.z)
			max_z = point.z;
		i++;
	}

	// Calculate cube info
	cube = &objf->bounding_box;

	cube->witdh = max_x - min_x;
	cube->height = max_y - min_y;
	cube->depth = max_z - min_z;

	cube->pos.x = (max_x + min_x) / 2.0f;
	cube->pos.y = (max_y + min_y) / 2.0f;
	cube->pos.z = (max_z + min_z) / 2.0f;
	vec3_add(&cube->pos, &objf->pos);

	cube->x_axis = (t_vec3){1.0f, 0.0f, 0.0f};
	cube->y_axis = (t_vec3){0.0f, 1.0f, 0.0f};
	cube_compute_constants(cube);
}
