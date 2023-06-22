/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compute_normal_ray.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouba <aderouba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 17:39:25 by tdubois           #+#    #+#             */
/*   Updated: 2023/06/22 19:04:40 by aderouba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt/app/app.h"

#include "minirt/app/scene/scene.h"
#include "minirt/app/utils/geometry/geometry.h"

#include "minirt/debug/debug.h"//TODO debug

static void	_compute_normal_ray_on_sphere(
				t_object const *sphere,
				t_ray const *ray,
				float distance,
				t_ray *normal);
static void	_compute_normal_ray_on_plane(
				t_object const *sphere,
				t_ray const *ray,
				t_intersect_info const *intersect_info,
				t_ray *normal);
static void	_compute_normal_ray_on_cylinder(
				t_object const *cylinder,
				t_ray const *ray,
				t_intersect_info const *intersect_info,
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
			t_intersect_info const *intersect_info,
			t_ray *normal)
{
	if (object->type == OBJ_SPHERE)
		_compute_normal_ray_on_sphere(object, ray, intersect_info->distance, normal);
	else if (object->type == OBJ_PLANE)
		_compute_normal_ray_on_plane(object, ray, intersect_info, normal);
	else if (object->type == OBJ_CYLINDER)
		_compute_normal_ray_on_cylinder(object, ray, intersect_info, normal);
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
				t_intersect_info const *intersect_info,
				t_ray *normal)
{
	t_plane const *const	geometry = &plane->value.as_plane;

	normal->pos = ray->pos;
	vec3_linear_transform(&normal->pos, intersect_info->distance, &ray->vec);
	if (intersect_info->sub_part_id == 0)
		normal->vec = geometry->normal;
	else
		normal->vec = geometry->rev_normal;
}

static void	_compute_normal_ray_on_cylinder(
				t_object const *cylinder,
				t_ray const *ray,
				t_intersect_info const *intersect_info,
				t_ray *normal)
{
	t_cylinder const *const	geometry = &cylinder->value.as_cylinder;
	t_vec3	vec;
	float	dot[2];
	float	heigth_on_cylinder;

	vec3_substract_into(&vec, &ray->pos, &geometry->pos);
	dot[0] = vec3_dot(&ray->vec, &geometry->axis);
	dot[1] = vec3_dot(&vec, &geometry->axis);
	heigth_on_cylinder = dot[0] * intersect_info->distance + dot[1];
	normal->pos = ray->pos;
	vec3_linear_transform(&normal->pos, intersect_info->distance, &ray->vec);
	if (intersect_info->sub_part_id == 1)
		normal->vec = cylinder->value.as_cylinder.bot.normal;
	else if (intersect_info->sub_part_id == 2)
		normal->vec = cylinder->value.as_cylinder.top.normal;
	else
	{
		vec = normal->pos;
		vec3_substract(&vec, &cylinder->value.as_cylinder.pos);
		normal->vec = geometry->axis;
		vec3_scale(&normal->vec, heigth_on_cylinder);
		vec3_substract(&vec, &normal->vec);
		normal->vec = vec;
		vec3_normalize(&normal->vec);
	}
}
