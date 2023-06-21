/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compute_normal_ray.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouba <aderouba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 17:39:25 by tdubois           #+#    #+#             */
/*   Updated: 2023/06/21 20:12:18 by aderouba         ###   ########.fr       */
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
static void	_compute_normal_ray_on_plane(
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
		_compute_normal_ray_on_sphere(object, ray, distance, normal);
	else if (object->type == OBJ_PLANE)
		_compute_normal_ray_on_plane(object, ray, distance, normal);
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

static void	_compute_normal_ray_on_plane(
				t_object const *plane,
				t_ray const *ray,
				float distance,
				t_ray *normal)
{
	t_plane const *const	geometry = &plane->value.as_plane;

	normal->pos = ray->pos;
	vec3_linear_transform(&normal->pos, distance, &ray->vec);
	if (vec3_dot(&geometry->normal, &ray->vec) < 0.0f)
		normal->vec = geometry->normal;
	else
		normal->vec = geometry->rev_normal;
}
