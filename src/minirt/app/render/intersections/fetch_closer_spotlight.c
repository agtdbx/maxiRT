/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fetch_closer_spotlight.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdubois <tdubois@student.42angouleme.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 16:43:28 by tdubois           #+#    #+#             */
/*   Updated: 2023/06/23 16:57:16 by tdubois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt/app/app.h"

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

#include "minirt/app/scene/scene.h"
#include "minirt/app/utils/color/color.h"

/**
 * @brief Given the distance to an object intersected by ray, fetch a spotlight
 * that is also intersected by ray, but closer than distance.
 *
 * @param[in] ray The ray
 * @param[in] lights The available spotlights
 * @param[in/out] distance Initially the distance to nearest object, may be
 * promoted as the distance to the closest spotlight.
 * @return A pointer to the nearest spotlight if any. Or NULL.
 */
t_light	*fetch_closer_spotlight(
			t_ray const *ray,
			t_light *lights,
			float *distance)
{
	float		cur_distance;
	t_light		*intersected_light;
	t_sphere	light_bulb;

	light_bulb.radius = 0.1;
	light_bulb.radius2 = 0.01;
	intersected_light = NULL;
	while (lights != NULL)
	{
		light_bulb.pos = lights->pos;
		if (test_intersection_with_sphere(ray, &light_bulb, &cur_distance)
			&& !(0 <= *distance && *distance <= cur_distance))
		{
			*distance = cur_distance;
			intersected_light = lights;
		}
		lights = lights->next;
	}
	return (intersected_light);
}
