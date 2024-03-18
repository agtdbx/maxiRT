/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_file_compute_constants_bonus.c              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auguste <auguste@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 19:51:32 by aderouba          #+#    #+#             */
/*   Updated: 2024/03/18 22:52:49 by auguste          ###   ########.fr       */
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

void	compute_objf_rectangle(
				t_object_file *objf,
				t_object_rectangle *rectangle);


void	compute_objf_bounding_box(
				t_object_file *objf);


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
