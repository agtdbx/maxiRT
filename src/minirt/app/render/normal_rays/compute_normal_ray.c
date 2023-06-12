/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compute_normal_ray.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdubois <tdubois@student.42angouleme.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 17:39:25 by tdubois           #+#    #+#             */
/*   Updated: 2023/06/12 17:42:51 by tdubois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt/app/app.h"

static void	_compute_normal_ray_on_sphere(
				t_sphere const *sphere,
				t_ray const *ray,
				float distance,
				t_ray *normal);

/**
 * @param[in] object
 * @param[in] ray
 * @param[in] distance
 * @param[out] normal
 */
void	compute_normal_ray(
				t_object const *object,
				t_ray const *ray,
				float distance,
				t_ray *normal)
{
	_compute_normal_ray_on_sphere(
			&object->value.as_sphere, ray, distance, normal);
}

static void	_compute_normal_ray_on_sphere(
				t_sphere const *sphere,
				t_ray const *ray,
				float distance,
				t_ray *normal)
{
	normal->pos = ray->pos;
	vec3_linear_transform(&normal->pos, distance, &ray->vec);
	vec3_substract_into(&normal->vec, &normal->pos, &sphere->pos);
	vec3_normalize(&normal->vec);
}
