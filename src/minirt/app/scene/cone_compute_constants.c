/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone_compute_constants.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auguste <auguste@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 19:51:32 by aderouba          #+#    #+#             */
/*   Updated: 2024/04/21 13:01:34 by auguste          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt/app/scene/scene.h"

#include <math.h>

#include "minirt/app/utils/geometry/geometry.h"

static void	_get_min_max_cone_end(
				float	min_max[6],
				t_vec3 *pos,
				float radius);
static float my_min(
				float nb1,
				float nb2);
static float my_max(
				float nb1,
				float nb2);
static void	_compute_cone_bounding_box(
					t_cone *cone,
					t_bounding_box *bbox);

/**
 * Compute constants from cone properties to facilitate further calculations
 * @param[out] cone
 */
void	cone_compute_constants(
			t_cone *cone,
			t_bounding_box *bbox)
{
	vec3_normalize(&cone->axis);
	cone->radius = cone->diameter / 2.0f;
	cone->radius2 = cone->radius * cone->radius;
	cone->end.pos = cone->pos;
	vec3_linear_transform(
		&cone->end.pos, cone->height, &cone->axis);
	cone->end.normal = cone->axis;
	cone->end.rev_normal = cone->axis;
	vec3_scale(&cone->end.rev_normal, -1.0f);
	cone->ratio = cone->radius / cone->height;
	cone->ratio = 1.0 + (cone->ratio * cone->ratio);

	_compute_cone_bounding_box(cone, bbox);
}

static void	_compute_cone_bounding_box(
					t_cone *cone,
					t_bounding_box *bbox)
{
	float	min_max_end[6];

	_get_min_max_cone_end(
		min_max_end, &cone->end.pos, cone->radius);

	bbox->min_x = my_min(min_max_end[0], cone->pos.x);
	bbox->max_x = my_max(min_max_end[1], cone->pos.x);
	bbox->min_y = my_min(min_max_end[2], cone->pos.y);
	bbox->max_y = my_max(min_max_end[3], cone->pos.y);
	bbox->min_z = my_min(min_max_end[4], cone->pos.z);
	bbox->max_z = my_max(min_max_end[5], cone->pos.z);

	compute_bounding_box_constants(bbox);
}

static void	_get_min_max_cone_end(
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
