/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere_compute_constants.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdubois <tdubois@student.42angouleme.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 09:05:15 by tdubois           #+#    #+#             */
/*   Updated: 2023/06/09 15:07:36 by tdubois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt/app/scene/scene_bonus.h"

#include <math.h>

#include "minirt/app/utils/geometry/geometry_bonus.h"

/**
 * Compute constants from sphere properties to facilitate further calculations
 * @param[out] sphere
 */
void	sphere_compute_constants(
			t_sphere *sphere)
{
	sphere->radius = sphere->diameter / 2.0f;
	sphere->radius2 = powf(sphere->radius, 2.0f);
}
