/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fetch_closest_intersections.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdubois <tdubois@student.42angouleme.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 15:56:02 by tdubois           #+#    #+#             */
/*   Updated: 2023/05/10 17:10:58 by tdubois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt/app/app.h>

#include <minirt/scene/scene.h>
#include <stddef.h>
#include <stdbool.h>

static inline bool	_test_intersection(
						t_ray const *ray,
						t_object const *object,
						float *distance);

extern inline t_object const	*fetch_closest_intersection(
									t_ray const *ray,
									t_object const *objects,
									float *distance)
{
	float			actual_distance;
	t_object const	*intersected_object;

	intersected_object = NULL;
	*distance = -1;
	while (objects != NULL)
	{
		if (_test_intersection(ray, objects, &actual_distance)
			&& actual_distance < *distance)
		{
			*distance = actual_distance;
			intersected_object = objects;
		}
		objects = objects->next;
	}
	return (intersected_object);
}

static inline bool	_test_intersection(
						t_ray const *ray,
						t_object const *object,
						float *distance)
{
	if (object->type == OBJ_SPHERE)
		return (test_intersection_with_sphere(
					ray, &object->value.as_sphere, distance));
	return (false);
}
