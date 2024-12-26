/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cube_pixel_pos.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damien <damien@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 15:49:28 by aderouba          #+#    #+#             */
/*   Updated: 2024/12/26 15:07:18 by damien           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt/app/app.h"

#include <math.h>

#include "minirt/app/utils/geometry/geometry.h"

static t_vec2	get_pixel_pos_x(
					t_cube const *cube,
					t_intersect_info const *intersect_info,
					t_vec3 *p);
static t_vec2	get_pixel_pos_y(
					t_cube const *cube,
					t_intersect_info const *intersect_info,
					t_vec3 *p);
static t_vec2	get_pixel_pos_z(
					t_cube const *cube,
					t_intersect_info const *intersect_info,
					t_vec3 *p);

t_vec2	get_cube_pixel_pos(
					t_cube const *cube,
					t_ray const *normal,
					t_intersect_info const *intersect_info)
{
	t_vec2	pixel;
	t_vec3	p;

	p = normal->pos;
	if (intersect_info->sub_part_id <= 1)
		pixel = get_pixel_pos_x(cube, intersect_info, &p);
	else if (intersect_info->sub_part_id <= 3)
		pixel = get_pixel_pos_y(cube, intersect_info, &p);
	else
		pixel = get_pixel_pos_z(cube, intersect_info, &p);
	pixel.x += 0.5f;
	pixel.y += 0.5f;
	return (pixel);
}

t_vec2	get_skybox_pixel_pos(
					t_skybox const *skybox,
					t_ray const *normal,
					t_intersect_info const *intersect_info)
{
	return get_cube_pixel_pos(&skybox->cube, normal, intersect_info);
}

static t_vec2	get_pixel_pos_x(
					t_cube const *cube,
					t_intersect_info const *intersect_info,
					t_vec3 *p)
{
	t_vec2	pixel;

	if (intersect_info->sub_part_id == 0)
	{
		vec3_substract(p, &cube->right.pos);
		pixel.x = -vec3_dot(&cube->z_axis, p) / cube->depth;
		pixel.y = -vec3_dot(&cube->y_axis, p) / cube->height;
	}
	else
	{
		vec3_substract(p, &cube->left.pos);
		pixel.x = vec3_dot(&cube->z_axis, p) / cube->depth;
		pixel.y = -vec3_dot(&cube->y_axis, p) / cube->height;
	}
	return (pixel);
}

static t_vec2	get_pixel_pos_y(
					t_cube const *cube,
					t_intersect_info const *intersect_info,
					t_vec3 *p)
{
	t_vec2	pixel;

	if (intersect_info->sub_part_id == 2)
	{
		vec3_substract(p, &cube->top.pos);
		pixel.x = vec3_dot(&cube->x_axis, p) / cube->witdh;
		pixel.y = vec3_dot(&cube->z_axis, p) / cube->depth;
	}
	else
	{
		vec3_substract(p, &cube->bot.pos);
		pixel.x = vec3_dot(&cube->x_axis, p) / cube->witdh;
		pixel.y = -vec3_dot(&cube->z_axis, p) / cube->depth;
	}
	return (pixel);
}

static t_vec2	get_pixel_pos_z(
					t_cube const *cube,
					t_intersect_info const *intersect_info,
					t_vec3 *p)
{
	t_vec2	pixel;

	if (intersect_info->sub_part_id == 4)
	{
		vec3_substract(p, &cube->front.pos);
		pixel.x = vec3_dot(&cube->x_axis, p) / cube->witdh;
		pixel.y = -vec3_dot(&cube->y_axis, p) / cube->height;
	}
	else
	{
		vec3_substract(p, &cube->back.pos);
		pixel.x = -vec3_dot(&cube->x_axis, p) / cube->witdh;
		pixel.y = -vec3_dot(&cube->y_axis, p) / cube->height;
	}
	return (pixel);
}
