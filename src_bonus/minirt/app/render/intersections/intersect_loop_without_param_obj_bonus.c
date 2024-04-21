/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_loop_without_param_obj_bonus.c           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auguste <auguste@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 19:47:22 by aderouba          #+#    #+#             */
/*   Updated: 2024/04/21 16:29:01 by auguste          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt/app/app_bonus.h"

static t_object	*get_closest_object(
					t_object *obj,
					t_object const *object,
					t_ray const *ray,
					t_intersect_info *intersect_info);

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
	t_ray				new_ray;
	t_object			*obj;
	t_object			*closest_obj;
	t_intersect_info	intersect_info;

	obj = scene->objects;
	closest_obj = get_closest_object(obj, object, ray, &intersect_info);
	if (closest_obj == NULL)
		return ((t_color){0});
	new_ray = *ray;
	new_ray.depth += 1;
	return (render_ray_on_object(scene, closest_obj, &new_ray, &intersect_info));
}

static t_object	*get_closest_object(
					t_object *obj,
					t_object const *object,
					t_ray const *ray,
					t_intersect_info *intersect_info)
{
	t_intersect_info	tmp_intersect_info;
	t_object			*closest_obj;

	intersect_info->distance = -1.0f;
	closest_obj = NULL;
	while (obj)
	{
		if (obj != object)
		{
			if (test_intersection_with_obj(ray, obj, &tmp_intersect_info)
				&& tmp_intersect_info.distance >= 0.0f
				&& (intersect_info->distance < 0.0f
					|| tmp_intersect_info.distance < intersect_info->distance))
			{
				intersect_info->distance = tmp_intersect_info.distance;
				intersect_info->sub_part_id = tmp_intersect_info.sub_part_id;
				closest_obj = obj;
			}
		}
		obj = obj->next;
	}
	return (closest_obj);
}
