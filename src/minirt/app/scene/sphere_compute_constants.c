/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere_compute_constants.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auguste <auguste@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 09:05:15 by tdubois           #+#    #+#             */
/*   Updated: 2024/04/21 12:30:16 by auguste          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt/app/scene/scene.h"

#include <math.h>

#include "minirt/app/utils/geometry/geometry.h"

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
