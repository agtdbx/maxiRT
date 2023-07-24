/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reflection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouba <aderouba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 11:41:46 by aderouba          #+#    #+#             */
/*   Updated: 2023/07/18 18:34:22 by tdubois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt/app/app_bonus.h"

#include "minirt/app/utils/geometry/geometry_bonus.h"

t_color	compute_reflected_color(
			t_object const *object,
			t_scene const *scene,
			t_ray const *ray,
			t_ray const *normal)
{
	t_vec3	tmp;
	t_ray	reflected_ray;

	if (object->reflection == 0.0f)
		return ((t_color){0});
	reflected_ray.pos = normal->pos;
	reflected_ray.vec = ray->vec;
	tmp = normal->vec;
	vec3_scale(&tmp, 2 * vec3_dot(&ray->vec, &normal->vec));
	vec3_substract(&reflected_ray.vec, &tmp);
	reflected_ray.depth = ray->depth + 1;
	return (intersect_loop_without_param_obj(object, scene, &reflected_ray));
}

t_color	reflection_outside_object(
			t_object const *object,
			t_scene const *scene,
			t_ray const *ray,
			t_ray const *normal)
{
	t_vec3	tmp;
	t_ray	transparency_ray;

	transparency_ray.pos = normal->pos;
	tmp = normal->vec;
	vec3_scale(&tmp,
		2 * vec3_dot(&ray->vec, &normal->vec));
	transparency_ray.vec = ray->vec;
	vec3_substract(&transparency_ray.vec, &tmp);
	vec3_normalize(&transparency_ray.vec);
	transparency_ray.depth = ray->depth + 1;
	return (intersect_loop_without_param_obj(object, scene, &transparency_ray));
}
