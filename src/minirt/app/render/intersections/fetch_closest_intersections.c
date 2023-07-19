/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fetch_closest_intersections.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouba <aderouba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 12:40:24 by tdubois           #+#    #+#             */
/*   Updated: 2023/07/19 19:35:57 by aderouba         ###   ########.fr       */
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
				t_intersect_info *intersect_info)
{
	t_intersect_info	actual_intersect_info;
	t_object			*intersected_object;

	intersected_object = NULL;
	intersect_info->distance = -1;
	while (objects != NULL)
	{
		if (test_intersection_with_obj(ray, objects, &actual_intersect_info)
			&& !(0 <= intersect_info->distance
				&& intersect_info->distance <= actual_intersect_info.distance))
		{
			intersect_info->distance = actual_intersect_info.distance;
			intersect_info->sub_part_id = actual_intersect_info.sub_part_id;
			intersected_object = objects;
		}
		objects = objects->next;
	}
	return (intersected_object);
}
