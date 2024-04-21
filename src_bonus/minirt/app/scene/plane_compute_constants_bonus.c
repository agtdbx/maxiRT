/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane_compute_constants_bonus.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auguste <auguste@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 19:51:32 by aderouba          #+#    #+#             */
/*   Updated: 2024/04/21 12:28:47 by auguste          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt/app/scene/scene_bonus.h"

#include <math.h>

#include "minirt/app/utils/geometry/geometry_bonus.h"

/**
 * Compute constants from plane properties to facilitate further calculations
 * @param[out] plane
 */
void	plane_compute_constants(
			t_plane *plane,
			t_bounding_box *bbox)
{
	vec3_normalize(&plane->normal);
	plane->rev_normal = plane->normal;
	vec3_scale(&plane->rev_normal, -1.0f);

	bbox->min_x = plane->pos.x - ((1.0f - plane->normal.x) * g_scene_radius);
	bbox->max_x = plane->pos.x + ((1.0f - plane->normal.x) * g_scene_radius);
	bbox->min_y = plane->pos.y - ((1.0f - plane->normal.y) * g_scene_radius);
	bbox->max_y = plane->pos.y + ((1.0f - plane->normal.y) * g_scene_radius);
	bbox->min_z = plane->pos.z - ((1.0f - plane->normal.z) * g_scene_radius);
	bbox->max_z = plane->pos.z + ((1.0f - plane->normal.z) * g_scene_radius);

	compute_bounding_box_constants(bbox);
}
