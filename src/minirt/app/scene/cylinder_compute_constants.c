/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_compute_constants.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouba <aderouba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 19:51:32 by aderouba          #+#    #+#             */
/*   Updated: 2023/06/23 16:20:04 by aderouba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt/app/scene/scene.h"

#include <math.h>
#include <stdio.h>

#include "minirt/app/utils/geometry/geometry.h"

/**
 * Compute constants from cylinder properties to facilitate further calculations
 * @param[out] cylinder
 */
void	cylinder_compute_constants(
			t_cylinder *cylinder)
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
}
