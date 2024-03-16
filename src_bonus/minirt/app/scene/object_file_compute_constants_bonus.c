/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_file_compute_constants_bonus.c              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auguste <auguste@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 19:51:32 by aderouba          #+#    #+#             */
/*   Updated: 2024/03/16 20:34:42 by auguste          ###   ########.fr       */
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


/**
 * Compute constants from cube properties to facilitate further calculations
 * @param[out] cube
 */
void	object_file_compute_constants(
			t_object_file *objf)
{
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
		//TODO : rotate point along objf axis
		// Move points along objf position
		vec3_add(&objf->real_vertices[i], &objf->pos);
		i++;
	}
}

#include <stdio.h>
static void	compute_objf_triangles(
				t_object_file *objf)
{
	int	i;

	i = 0;
	while (i < objf->nb_triangles)
	{
		t_objf_triangle *triangle = &objf->triangles[i];

		// Get points from real vertice
		triangle->point1 = objf->real_vertices[triangle->vertice_1];
		triangle->point2 = objf->real_vertices[triangle->vertice_2];
		triangle->point3 = objf->real_vertices[triangle->vertice_3];

		// Compute triangle constants
		vec3_substract_into(&triangle->v1, &triangle->point2, &triangle->point1);
		vec3_substract_into(&triangle->v2, &triangle->point3, &triangle->point1);
		triangle->normal.x = (triangle->v1.y * triangle->v2.z)
							- (triangle->v1.z * triangle->v2.y);
		triangle->normal.y = (triangle->v1.z * triangle->v2.x)
							- (triangle->v1.x * triangle->v2.z);
		triangle->normal.z = (triangle->v1.x * triangle->v2.y)
							- (triangle->v1.y * triangle->v2.x);
		vec3_normalize(&triangle->normal);
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
		point = objf->vertices[i];
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

	cube->pos.x = cube->witdh / 2.0f;
	cube->pos.y = cube->height / 2.0f;
	cube->pos.z = cube->depth / 2.0f;
	vec3_add(&cube->pos, &objf->pos);

	cube->x_axis = objf->x_axis;
	cube->y_axis = objf->y_axis;
	cube_compute_constants(cube);
}
