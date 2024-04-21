/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_compute_constants_bonus.c                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auguste <auguste@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 19:51:32 by aderouba          #+#    #+#             */
/*   Updated: 2024/04/21 11:51:10 by auguste          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt/app/scene/scene_bonus.h"

#include <math.h>
#include <stdio.h>

#include "minirt/app/utils/geometry/geometry_bonus.h"

static void	_compute_cylinder_bounding_box(
					t_cylinder *cylinder,
					t_bounding_box *bbox);
static void	_get_min_max_cylinder_end(
				float	min_max[6],
				t_vec3 *pos,
				float radius);
static float my_min(
				float nb1,
				float nb2);
static float my_max(
				float nb1,
				float nb2);


/**
 * Compute constants from cylinder properties to facilitate further calculations
 * @param[out] cylinder
 */
void	cylinder_compute_constants(
			t_cylinder *cylinder,
			t_bounding_box *bbox)
{
	t_vec3	rev_axis;

	vec3_normalize(&cylinder->axis);
	cylinder->radius = cylinder->diameter / 2.0f;
	cylinder->radius2 = cylinder->radius * cylinder->radius;
	cylinder->half_height = cylinder->height / 2.0f;
	rev_axis = cylinder->axis;
	vec3_scale(&rev_axis, -1.0f);
	cylinder->bot.pos = cylinder->pos;
	vec3_linear_transform(
		&cylinder->bot.pos, cylinder->height / 2.0f, &rev_axis);
	cylinder->bot.normal = rev_axis;
	cylinder->bot.rev_normal = cylinder->axis;
	cylinder->top.pos = cylinder->pos;
	vec3_linear_transform(
		&cylinder->top.pos, cylinder->height / 2.0f, &cylinder->axis);
	cylinder->top.normal = cylinder->axis;
	cylinder->top.rev_normal = rev_axis;

	_compute_cylinder_bounding_box(cylinder, bbox);
}

static void	_compute_cylinder_bounding_box(
					t_cylinder *cylinder,
					t_bounding_box *bbox)
{
	float	min_max_top[6];
	float	min_max_bot[6];

	_get_min_max_cylinder_end(
		min_max_top, &cylinder->top.pos, cylinder->radius);
	_get_min_max_cylinder_end(
		min_max_bot, &cylinder->bot.pos, cylinder->radius);

	bbox->min_x = my_min(min_max_top[0], min_max_bot[0]);
	bbox->max_x = my_max(min_max_top[1], min_max_bot[1]);
	bbox->min_y = my_min(min_max_top[2], min_max_bot[2]);
	bbox->max_y = my_max(min_max_top[3], min_max_bot[3]);
	bbox->min_z = my_min(min_max_top[4], min_max_bot[4]);
	bbox->max_z = my_max(min_max_top[5], min_max_bot[5]);

	compute_bounding_box_constants(bbox);
}

static void	_get_min_max_cylinder_end(
				float	min_max[6],
				t_vec3 *pos,
				float radius)
{
	min_max[0] = pos->x - radius;
	min_max[1] = pos->x + radius;
	min_max[2] = pos->y - radius;
	min_max[3] = pos->y + radius;
	min_max[4] = pos->z - radius;
	min_max[5] = pos->z + radius;
}

static float my_min(
				float nb1,
				float nb2)
{
	if (nb1 < nb2)
		return (nb1);
	return (nb2);
}

static float my_max(
				float nb1,
				float nb2)
{
	if (nb1 > nb2)
		return (nb1);
	return (nb2);
}
