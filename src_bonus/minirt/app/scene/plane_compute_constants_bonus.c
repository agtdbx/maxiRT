/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane_compute_constants.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouba <aderouba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 19:51:32 by aderouba          #+#    #+#             */
/*   Updated: 2023/06/23 16:20:38 by aderouba         ###   ########.fr       */
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
			t_plane *plane)
{
	vec3_normalize(&plane->normal);
	plane->rev_normal = plane->normal;
	vec3_scale(&plane->normal, -1.0f);
}
