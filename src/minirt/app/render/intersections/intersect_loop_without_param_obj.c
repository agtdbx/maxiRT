/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_loop_without_param_obj.c                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouba <aderouba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 19:47:22 by aderouba          #+#    #+#             */
/*   Updated: 2023/06/20 19:54:15 by aderouba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt/app/app.h"

/**
 * Do a loop of intersection with all object without the parameter's one
 * @param[in] object
 * @param[in] scene
 * @param[in] ray
 * @returns The color of the pixel at the ray intersection
 */
t_color	intersect_loop_without_param_obj(
			t_object const *object,
			t_scene const *scene,
			t_ray const *ray)
{
	t_object		*obj;
	t_object		*closest_obj;
	float			dst;
	float			tmp_dst;

	dst = -1.0f;
	closest_obj = NULL;
	obj = scene->objects;
	while (obj)
	{
		if (obj != object)
		{
			if (test_intersection_with_obj(ray, obj, &tmp_dst)
				&& tmp_dst >= 0.0f && (dst < 0.0f || tmp_dst < dst))
			{
				dst = tmp_dst;
				closest_obj = obj;
			}
		}
		obj = obj->next;
	}
	if (closest_obj == NULL)
		return ((t_color){0});
	return (render_ray_on_object(scene, closest_obj, ray, dst));
}
