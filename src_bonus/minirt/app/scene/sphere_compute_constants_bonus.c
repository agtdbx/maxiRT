/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere_compute_constants_bonus.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auguste <auguste@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 09:05:15 by tdubois           #+#    #+#             */
/*   Updated: 2024/04/21 12:30:16 by auguste          ###   ########.fr       */
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
			t_sphere *sphere,
			t_bounding_box *bbox)
{
	sphere->radius = sphere->diameter / 2.0f;
	sphere->radius2 = powf(sphere->radius, 2.0f);

	bbox->min_x = sphere->pos.x - sphere->radius;
	bbox->max_x = sphere->pos.x + sphere->radius;
	bbox->min_y = sphere->pos.y - sphere->radius;
	bbox->max_y = sphere->pos.y + sphere->radius;
	bbox->min_z = sphere->pos.z - sphere->radius;
	bbox->max_z = sphere->pos.z + sphere->radius;

	compute_bounding_box_constants(bbox);
}
