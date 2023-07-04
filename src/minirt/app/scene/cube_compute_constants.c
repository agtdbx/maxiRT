/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube_compute_constants.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouba <aderouba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 19:51:32 by aderouba          #+#    #+#             */
/*   Updated: 2023/07/04 18:38:46 by aderouba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt/app/scene/scene.h"

#include <math.h>
#include <stdio.h>

#include "minirt/app/utils/geometry/geometry.h"

/**
 * Compute constants from cube properties to facilitate further calculations
 * @param[out] cube
 */
void	cube_compute_constants(
			t_cube *cube)
{
	t_vec3	rev_x_axis;
	t_vec3	rev_y_axis;
	t_vec3	rev_z_axis;

	vec3_cross(&cube->x_axis, &cube->y_axis, &cube->z_axis);
	vec3_normalize(&cube->x_axis);
	vec3_normalize(&cube->y_axis);
	vec3_normalize(&cube->z_axis);

	rev_x_axis = cube->x_axis;
	vec3_scale(&rev_x_axis, -1.0f);
	rev_y_axis = cube->y_axis;
	vec3_scale(&rev_y_axis, -1.0f);
	rev_z_axis = cube->z_axis;
	vec3_scale(&rev_z_axis, -1.0f);

	cube->half_witdh = cube->witdh / 2.0f;
	cube->half_height = cube->height / 2.0f;
	cube->half_depth= cube->depth / 2.0f;

	// Right
	cube->right.pos = cube->pos;
	vec3_linear_transform(
		&cube->right.pos, cube->half_witdh, &cube->x_axis);
	cube->right.normal = cube->x_axis;
	cube->right.rev_normal = rev_x_axis;
	// Left
	cube->left.pos = cube->pos;
	vec3_linear_transform(
		&cube->left.pos, cube->half_witdh, &rev_x_axis);
	cube->left.normal = rev_x_axis;
	cube->left.rev_normal = cube->x_axis;
	// Top
	cube->top.pos = cube->pos;
	vec3_linear_transform(
		&cube->top.pos, cube->half_height, &cube->y_axis);
	cube->top.normal = cube->y_axis;
	cube->top.rev_normal = rev_y_axis;
	// Bot
	cube->bot.pos = cube->pos;
	vec3_linear_transform(
		&cube->bot.pos, cube->half_height, &rev_y_axis);
	cube->bot.normal = rev_y_axis;
	cube->bot.rev_normal = cube->y_axis;
	// Front
	cube->front.pos = cube->pos;
	vec3_linear_transform(
		&cube->front.pos, cube->half_depth, &cube->z_axis);
	cube->front.normal = cube->z_axis;
	cube->front.rev_normal = rev_z_axis;
	// Back
	cube->back.pos = cube->pos;
	vec3_linear_transform(
		&cube->back.pos, cube->half_depth, &rev_z_axis);
	cube->back.normal = rev_z_axis;
	cube->back.rev_normal = cube->z_axis;
}
