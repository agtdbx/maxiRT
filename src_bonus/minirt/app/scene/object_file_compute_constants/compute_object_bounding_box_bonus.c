/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compute_object_bounding_box_bonus.c                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auguste <auguste@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 22:51:50 by auguste           #+#    #+#             */
/*   Updated: 2024/03/18 22:52:32 by auguste          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt/app/scene/scene_bonus.h"

#include <math.h>

#include "minirt/app/utils/geometry/geometry_bonus.h"

static void	calculate_bounding_box_bounds(
				t_object_file *objf,
				float	bounds_x[2],
				float	bounds_y[2],
				float	bounds_z[2]);
static void	set_min_max(
				float *nb,
				float bounds[2]);


void	compute_objf_bounding_box(
				t_object_file *objf)
{
	float	bounds_x[2];
	float	bounds_y[2];
	float	bounds_z[2];
	t_cube	*cube;

	// Get mins and max
	calculate_bounding_box_bounds(objf, bounds_x, bounds_y, bounds_z);

	// Calculate cube info
	cube = &objf->bounding_box;

	cube->witdh = bounds_x[1] - bounds_x[0];
	cube->height = bounds_y[1] - bounds_y[0];
	cube->depth = bounds_z[1] - bounds_z[0];

	cube->pos.x = (bounds_x[1] + bounds_x[0]) / 2.0f;
	cube->pos.y = (bounds_y[1] + bounds_y[0]) / 2.0f;
	cube->pos.z = (bounds_z[1] + bounds_z[0]) / 2.0f;
	vec3_add(&cube->pos, &objf->pos);

	cube->x_axis = (t_vec3){1.0f, 0.0f, 0.0f};
	cube->y_axis = (t_vec3){0.0f, 1.0f, 0.0f};
	cube_compute_constants(cube);
}

static void	calculate_bounding_box_bounds(
				t_object_file *objf,
				float	bounds_x[2],
				float	bounds_y[2],
				float	bounds_z[2])
{
	int		i;
	t_vec3	point;

	i = 0;
	bounds_x[0] = 0;
	bounds_y[0] = 0;
	bounds_z[0] = 0;
	bounds_x[1] = 0;
	bounds_y[1] = 0;
	bounds_z[1] = 0;
	while (i < objf->nb_vertices)
	{
		point = objf->real_vertices[i];
		vec3_substract(&point, &objf->pos);
		set_min_max(&point.x, bounds_x);
		set_min_max(&point.y, bounds_y);
		set_min_max(&point.z, bounds_z);
		i++;
	}
}

static void	set_min_max(
				float *nb,
				float bounds[2])
{
	if (bounds[0] > *nb)
		bounds[0] = *nb;
	if (bounds[1] < *nb)
		bounds[1] = *nb;
}
