/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_file_compute_constants.c              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gugus <gugus@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 19:51:32 by aderouba          #+#    #+#             */
/*   Updated: 2024/06/16 11:58:08 by gugus            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt/app/scene/scene.h"

#include <math.h>

#include "minirt/app/utils/geometry/geometry.h"

static void	axis_checker(
				t_object_file *objf);
static void	compute_objf_vertices(
				t_object_file *objf);
static void	compute_objf_polygons(
				t_object_file *objf);

/**
 * Compute constants from object file properties to facilitate further
 * calculations
 * @param[out] objf
 */
void	object_file_compute_constants(
			t_object_file *objf)
{
	axis_checker(objf);

	vec3_cross(&objf->x_axis, &objf->y_axis, &objf->z_axis);
	vec3_normalize(&objf->x_axis);
	vec3_normalize(&objf->y_axis);
	vec3_normalize(&objf->z_axis);

	// Compute all vertices
	compute_objf_vertices(objf);

	// Compute all polygons
	compute_objf_polygons(objf);

	// Compute bounding boxes
	compute_objf_bounding_boxes(objf);
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
			compute_objf_triangle(
				objf,
				&objf->polygons[i].value.as_objf_triangle,
				&objf->polygons[i].bounding_box);
		else if (objf->polygons[i].type == OBJF_RECTANGLE)
			compute_objf_rectangle(
				objf,
				&objf->polygons[i].value.as_objf_rectangle,
				&objf->polygons[i].bounding_box);
		i++;
	}
}
