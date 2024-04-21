/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube_compute_constants_bonus.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auguste <auguste@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 19:51:32 by aderouba          #+#    #+#             */
/*   Updated: 2024/04/21 12:29:56 by auguste          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt/app/scene/scene_bonus.h"

#include <math.h>
#include <stdio.h>

#include "minirt/app/utils/geometry/geometry_bonus.h"
#include "minirt/app/utils/space_partition/space_partition.h"

static void	init_face(
				t_cube const *cube,
				t_plane *face,
				t_vec3 const *axis,
				float dist);
static void	axis_checker(
				t_cube *cube);

static void	get_points_of_face(
				t_vec3 points[4],
				t_vec3 *pos,
				t_vec3 *true_right,
				t_vec3 *true_up);
static void	_compute_cube_bounding_box(
					t_cube *cube,
					t_bounding_box *bbox);


/**
 * Compute constants from cube properties to facilitate further calculations
 * @param[out] cube
 */
void	cube_compute_constants(
			t_cube *cube,
			t_bounding_box *bbox)
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

	_compute_cube_bounding_box(cube, bbox);
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

static void	_compute_cube_bounding_box(
					t_cube *cube,
					t_bounding_box *bbox)
{
	t_vec3			points_front[4]; // ul ur dr dl
	t_vec3			points_back[4]; // ul ur dr dl
	t_vec3			true_right;
	t_vec3			true_up;

	vec3_scale_into(&true_right, &cube->x_axis, cube->half_witdh);
	vec3_scale_into(&true_up, &cube->y_axis, cube->half_height);

	get_points_of_face(points_front, &cube->pos, &true_right, &true_up);
	get_points_of_face(points_back, &cube->pos, &true_right, &true_up);

	bbox->min_x = points_front[0].x;
	bbox->max_x = points_front[0].x;
	bbox->min_y = points_front[0].y;
	bbox->max_y = points_front[0].y;
	bbox->min_z = points_front[0].z;
	bbox->max_z = points_front[0].z;

	set_min_max(&bbox->min_x, &bbox->max_x, &points_front[1].x);
	set_min_max(&bbox->min_y, &bbox->max_y, &points_front[1].y);
	set_min_max(&bbox->min_z, &bbox->max_z, &points_front[1].z);

	set_min_max(&bbox->min_x, &bbox->max_x, &points_front[2].x);
	set_min_max(&bbox->min_y, &bbox->max_y, &points_front[2].y);
	set_min_max(&bbox->min_z, &bbox->max_z, &points_front[2].z);

	set_min_max(&bbox->min_x, &bbox->max_x, &points_front[3].x);
	set_min_max(&bbox->min_y, &bbox->max_y, &points_front[3].y);
	set_min_max(&bbox->min_z, &bbox->max_z, &points_front[3].z);

	set_min_max(&bbox->min_x, &bbox->max_x, &points_back[0].x);
	set_min_max(&bbox->min_y, &bbox->max_y, &points_back[0].y);
	set_min_max(&bbox->min_z, &bbox->max_z, &points_back[0].z);

	set_min_max(&bbox->min_x, &bbox->max_x, &points_back[1].x);
	set_min_max(&bbox->min_y, &bbox->max_y, &points_back[1].y);
	set_min_max(&bbox->min_z, &bbox->max_z, &points_back[1].z);

	set_min_max(&bbox->min_x, &bbox->max_x, &points_back[2].x);
	set_min_max(&bbox->min_y, &bbox->max_y, &points_back[2].y);
	set_min_max(&bbox->min_z, &bbox->max_z, &points_back[2].z);

	set_min_max(&bbox->min_x, &bbox->max_x, &points_back[3].x);
	set_min_max(&bbox->min_y, &bbox->max_y, &points_back[3].y);
	set_min_max(&bbox->min_z, &bbox->max_z, &points_back[3].z);

	compute_bounding_box_constants(bbox);
}


static void	get_points_of_face(
				t_vec3 points[4],
				t_vec3 *pos,
				t_vec3 *true_right,
				t_vec3 *true_up)
{
	// ul
	vec3_substract_into(&points[0], pos, true_right);
	vec3_add(&points[0], true_up);

	// ur
	vec3_add_into(&points[1], pos, true_right);
	vec3_add(&points[1], true_up);

	// dr
	vec3_add_into(&points[2], pos, true_right);
	vec3_substract(&points[2], true_up);

	// dl
	vec3_substract_into(&points[3], pos, true_right);
	vec3_substract(&points[3], true_up);
}
