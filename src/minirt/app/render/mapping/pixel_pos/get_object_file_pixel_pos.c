/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_object_file_pixel_pos.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auguste <auguste@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 15:49:28 by aderouba          #+#    #+#             */
/*   Updated: 2024/03/17 21:46:56 by auguste          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt/app/app.h"

#include <math.h>

#include "minirt/app/utils/geometry/geometry.h"

static t_vec2	get_object_file_triangle_pixel_pos(
					t_object_triangle const *triangle,
					t_ray const *vec3_normalize_into);
static t_vec2	get_object_file_rectangle_pixel_pos(
					t_object_rectangle const *rectangle,
					t_ray const *normal);

t_vec2	get_object_file_pixel_pos(
					t_object_file const *objf,
					t_ray const *normal,
					t_intersect_info const *intersect_info)
{
	t_object_polygon	*const	polygon =
							&objf->polygons[intersect_info->sub_part_id];

	if (polygon->type == OBJF_TRIANGLE)
		return (get_object_file_triangle_pixel_pos(
					&polygon->value.as_objf_triangle, normal));
	if (polygon->type == OBJF_RECTANGLE)
		return (get_object_file_rectangle_pixel_pos(
					&polygon->value.as_objf_rectangle, normal));
	return ((t_vec2){0});
}

static t_vec2	get_object_file_triangle_pixel_pos(
					t_object_triangle const *triangle,
					t_ray const *normal)
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
					t_ray const *normal)
{
	t_vec2	pixel;
	t_vec3	p;

	p = normal->pos;
	vec3_substract(&p, &rectangle->point1);
	if (rectangle->inv_width != 0.0f)
		pixel.x = -vec3_dot(&rectangle->x_axis, &p) * rectangle->inv_width;
	else
		pixel.x = 0.0f;

	if (rectangle->inv_height != 0.0f)
		pixel.y = -vec3_dot(&rectangle->y_axis, &p) * rectangle->inv_height;
	else
		pixel.y = 0.0f;

	return (pixel);
}
