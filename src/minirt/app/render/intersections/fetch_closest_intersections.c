/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fetch_closest_intersections.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdubois <tdubois@student.42angouleme.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 15:56:02 by tdubois           #+#    #+#             */
/*   Updated: 2023/06/23 16:39:44 by tdubois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt/app/app.h"

#include <stddef.h>
#include <stdbool.h>

#include "minirt/app/scene/scene.h"

/**
 * Fetch closest object intersected by ray
 * @param[in] ray
 * @param[in] objects
 * @param[out] distance The distance to the closest object or NULL.
 * @returns A pointer to the closest object
 * or NULL if ray did not intercept any object.
 */
t_object	*fetch_closest_intersection(
				t_ray const *ray,
				t_object *objects,
				float *distance)
{
	float		cur_distance;
	float		min_distance;
	t_object	*intersected_object;

	intersected_object = NULL;
	min_distance = -1;
	while (objects != NULL)
	{
		if (test_intersection_with_obj(ray, objects, &cur_distance)
			&& !(0 <= min_distance && min_distance <= cur_distance))
		{
			min_distance = cur_distance;
			intersected_object = objects;
		}
		objects = objects->next;
	}
	if (distance != NULL)
	{
		*distance = min_distance;
	}
	return (intersected_object);
}
