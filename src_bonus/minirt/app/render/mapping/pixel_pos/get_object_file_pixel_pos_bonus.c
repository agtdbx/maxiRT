/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_object_file_pixel_pos_bonus.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auguste <auguste@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 15:49:28 by aderouba          #+#    #+#             */
/*   Updated: 2024/03/17 20:13:45 by auguste          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt/app/app_bonus.h"

#include <math.h>

#include "minirt/app/utils/geometry/geometry_bonus.h"

static t_vec2	get_object_file_triangle_pixel_pos(
					t_object_triangle const *triangle,
					t_ray const *normal,
					t_intersect_info const *intersect_info);
static t_vec2	get_object_file_rectangle_pixel_pos(
					t_object_rectangle const *rectangle,
					t_ray const *normal,
					t_intersect_info const *intersect_info);

t_vec2	get_object_file_pixel_pos(
					t_object_file const *objf,
					t_ray const *normal,
					t_intersect_info const *intersect_info)
{
	t_object_polygon	*const	polygon =
							&objf->polygons[intersect_info->sub_part_id];

	if (polygon->type == OBJF_TRIANGLE)
		return (get_object_file_triangle_pixel_pos(
					&polygon->value.as_objf_triangle, normal, intersect_info));
	if (polygon->type == OBJF_RECTANGLE)
		return (get_object_file_rectangle_pixel_pos(
					&polygon->value.as_objf_rectangle, normal, intersect_info));
}

static t_vec2	get_object_file_triangle_pixel_pos(
					t_object_triangle const *triangle,
					t_ray const *normal,
					t_intersect_info const *intersect_info)
{
	t_vec2						pixel;
	float						PCx;
	float						PCy;

	if (triangle->div_part == 0.0f)
	{
		pixel.x = 0.0f;
		pixel.y = 0.0f;
		return (pixel);
	}
	if (triangle->pixel_pos_base == 0)
	{
		PCx = normal->pos.x - triangle->point3.x;
		PCy = normal->pos.y - triangle->point3.y;
	}
	else if (triangle->pixel_pos_base == 1)
	{
		PCx = normal->pos.x - triangle->point3.x;
		PCy = normal->pos.z - triangle->point3.z;
	}
	else
	{
		PCx = normal->pos.z - triangle->point3.z;
		PCy = normal->pos.y - triangle->point3.y;
	}
	pixel.x = ((triangle->BCy * PCx) + (triangle->CBx * PCy)) * triangle->div_part;
	pixel.y = ((triangle->CAy * PCx) + (triangle->ACx * PCy)) * triangle->div_part;
	return (pixel);
}


static t_vec2	get_object_file_rectangle_pixel_pos(
					t_object_rectangle const *rectangle,
					t_ray const *normal,
					t_intersect_info const *intersect_info)
{
	t_vec2	pixel;

	pixel.x = 0.0f;
	pixel.y = 0.0f;
	return (pixel);
}
