/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_compute_constants.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouba <aderouba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 19:01:39 by aderouba          #+#    #+#             */
/*   Updated: 2025/01/17 19:02:39 by aderouba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt/app/scene/scene.h"

#include <math.h>

#include "minirt/app/utils/geometry/geometry.h"

/**
 * Compute constants from plane properties to facilitate further calculations
 * @param[out] plane
 */
void	light_compute_constants(
			t_light *light)
{
	vec3_normalize(&light->dir);

	light->min_angle = 360.0f - light->angle;
}
