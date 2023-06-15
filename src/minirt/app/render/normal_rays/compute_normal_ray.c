/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compute_normal_ray.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdubois <tdubois@student.42angouleme.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 17:39:25 by tdubois           #+#    #+#             */
/*   Updated: 2023/06/15 17:10:25 by tdubois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt/app/app.h"

#include "minirt/app/scene/scene.h"
#include "minirt/app/utils/geometry/geometry.h"

static void	_compute_normal_ray_on_sphere(
				t_object const *sphere,
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
	if (object->type == OBJ_SPHERE)
	{
		_compute_normal_ray_on_sphere(object, ray, distance, normal);
	}
}

static void	_compute_normal_ray_on_sphere(
				t_object const *sphere,
				t_ray const *ray,
				float distance,
				t_ray *normal)
{
	t_sphere const *const	geometry = &sphere->value.as_sphere;

	normal->pos = ray->pos;
	vec3_linear_transform(&normal->pos, distance, &ray->vec);
	vec3_substract_into(&normal->vec, &normal->pos, &geometry->pos);
	vec3_normalize(&normal->vec);
}
