/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compute_object_rectangle_bonus.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auguste <auguste@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 22:48:40 by auguste           #+#    #+#             */
/*   Updated: 2024/04/21 12:34:25 by auguste          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt/app/scene/scene_bonus.h"

#include <math.h>

#include "minirt/app/utils/geometry/geometry_bonus.h"
#include "minirt/app/utils/space_partition/space_partition.h"

static void	_compute_object_rectangle_bounding_box(
				t_bounding_box *bbox,
				t_object_rectangle *rectangle);

void	compute_objf_rectangle(
			t_object_file *objf,
			t_object_rectangle *rectangle,
			t_bounding_box *bbox)
{
	t_vec3	p2_p1;
	t_vec3	p3_p1;
	t_vec3	p4_p1;

	// Get points from real vertice
	rectangle->point1 = objf->real_vertices[rectangle->vertice_1];
	rectangle->point2 = objf->real_vertices[rectangle->vertice_2];
	rectangle->point3 = objf->real_vertices[rectangle->vertice_3];
	rectangle->point4 = objf->real_vertices[rectangle->vertice_4];

	// Compute normal
	vec3_substract_into(&p2_p1, &rectangle->point2, &rectangle->point1);
	vec3_substract_into(&p3_p1, &rectangle->point3, &rectangle->point1);
	vec3_cross(&p2_p1, &p3_p1, &rectangle->normal);
	vec3_normalize(&rectangle->normal);

	// Compute bases
	vec3_substract_into(&p4_p1, &rectangle->point4, &rectangle->point1);
	vec3_scale_into(&rectangle->x_axis, &p4_p1, -1.0f);
	vec3_scale_into(&rectangle->y_axis, &p2_p1, -1.0f);
	rectangle->inv_width = vec3_norm(&rectangle->x_axis);
	if (rectangle->inv_width != 0.0f)
	{
		rectangle->inv_width = 1.0f / rectangle->inv_width;
		vec3_scale(&rectangle->x_axis, rectangle->inv_width);
	}
	rectangle->inv_height = vec3_norm(&rectangle->y_axis);
	if (rectangle->inv_height != 0.0f)
	{
		rectangle->inv_height = 1.0f / rectangle->inv_height;
		vec3_scale(&rectangle->y_axis, rectangle->inv_height);
	}
	_compute_object_rectangle_bounding_box(bbox, rectangle);
}

static void	_compute_object_rectangle_bounding_box(
				t_bounding_box *bbox,
				t_object_rectangle *rectangle)
{
	bbox->min_x = rectangle->point1.x;
	bbox->max_x = rectangle->point1.x;
	bbox->min_y = rectangle->point1.y;
	bbox->max_y = rectangle->point1.y;
	bbox->min_z = rectangle->point1.z;
	bbox->max_z = rectangle->point1.z;

	set_min_max(&bbox->min_x, &bbox->max_x, &rectangle->point2.x);
	set_min_max(&bbox->min_y, &bbox->max_y, &rectangle->point2.y);
	set_min_max(&bbox->min_z, &bbox->max_z, &rectangle->point2.z);

	set_min_max(&bbox->min_x, &bbox->max_x, &rectangle->point3.x);
	set_min_max(&bbox->min_y, &bbox->max_y, &rectangle->point3.y);
	set_min_max(&bbox->min_z, &bbox->max_z, &rectangle->point3.z);

	set_min_max(&bbox->min_x, &bbox->max_x, &rectangle->point4.x);
	set_min_max(&bbox->min_y, &bbox->max_y, &rectangle->point4.y);
	set_min_max(&bbox->min_z, &bbox->max_z, &rectangle->point4.z);
}
