/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube_compute_constants.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouba <aderouba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 19:51:32 by aderouba          #+#    #+#             */
/*   Updated: 2023/07/23 12:59:56 by aderouba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt/app/scene/scene_bonus.h"

#include <math.h>
#include <stdio.h>

#include "minirt/app/utils/geometry/geometry_bonus.h"

static void	init_face(
				t_cube const *cube,
				t_plane *face,
				t_vec3 const *axis,
				float dist);
static void	axis_checker(
				t_cube *cube);

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
	rev_y_axis = cube->y_axis;
	rev_z_axis = cube->z_axis;
	vec3_scale(&rev_x_axis, -1.0f);
	vec3_scale(&rev_y_axis, -1.0f);
	vec3_scale(&rev_z_axis, -1.0f);
	cube->half_witdh = cube->witdh / 2.0f;
	cube->half_height = cube->height / 2.0f;
	cube->half_depth = cube->depth / 2.0f;
	init_face(cube, &cube->right, &cube->x_axis, cube->half_witdh);
	init_face(cube, &cube->left, &rev_x_axis, cube->half_witdh);
	init_face(cube, &cube->top, &cube->y_axis, cube->half_height);
	init_face(cube, &cube->bot, &rev_y_axis, cube->half_height);
	init_face(cube, &cube->front, &cube->z_axis, cube->half_depth);
	init_face(cube, &cube->back, &rev_z_axis, cube->half_depth);
}

/**
 * Compute constants from cube properties when there are modified in menu
 * @param[out] cube
 */
void	cube_compute_constants_from_menu(
			t_cube *cube)
{
	t_vec3	rev_x_axis;
	t_vec3	rev_y_axis;
	t_vec3	rev_z_axis;

	axis_checker(cube);
	vec3_cross(&cube->x_axis, &cube->y_axis, &cube->z_axis);
	vec3_normalize(&cube->x_axis);
	vec3_normalize(&cube->y_axis);
	vec3_normalize(&cube->z_axis);
	rev_x_axis = cube->x_axis;
	rev_y_axis = cube->y_axis;
	rev_z_axis = cube->z_axis;
	vec3_scale(&rev_x_axis, -1.0f);
	vec3_scale(&rev_y_axis, -1.0f);
	vec3_scale(&rev_z_axis, -1.0f);
	cube->half_witdh = cube->witdh / 2.0f;
	cube->half_height = cube->height / 2.0f;
	cube->half_depth = cube->depth / 2.0f;
	init_face(cube, &cube->right, &cube->x_axis, cube->half_witdh);
	init_face(cube, &cube->left, &rev_x_axis, cube->half_witdh);
	init_face(cube, &cube->top, &cube->y_axis, cube->half_height);
	init_face(cube, &cube->bot, &rev_y_axis, cube->half_height);
	init_face(cube, &cube->front, &cube->z_axis, cube->half_depth);
	init_face(cube, &cube->back, &rev_z_axis, cube->half_depth);
}

static void	axis_checker(
				t_cube *cube)
{
	if (vec3_dot(&cube->x_axis, &cube->y_axis) != 0.0f)
	{
		if (vec3_dot(&cube->x_axis, &cube->z_axis) != 0.0f)
			vec3_cross(&cube->y_axis, &cube->z_axis, &cube->x_axis);
		else
			vec3_cross(&cube->x_axis, &cube->z_axis, &cube->y_axis);
	}
}

static void	init_face(
				t_cube const *cube,
				t_plane *face,
				t_vec3 const *axis,
				float dist)
{
	face->pos = cube->pos;
	vec3_linear_transform(
		&face->pos, dist, axis);
	face->normal = *axis;
	vec3_scale_into(&face->rev_normal, &face->normal, -1.0f);
}
