/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_ray_on_sphere.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdubois <tdubois@student.42angouleme.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 10:06:32 by tdubois           #+#    #+#             */
/*   Updated: 2023/06/09 14:08:48 by tdubois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt/app/app.h"

#include <stdint.h>

#include "minirt/app/scene/scene.h"
#include "minirt/app/utils/color/color.h"
#include "minirt/app/utils/geometry/geometry.h"
#include "minirt/debug/debug.h"//TODO debug

static void	_compute_normal_ray(
				t_sphere const *sphere,
				t_ray const *ray,
				float distance,
				t_ray *normal);

int32_t	render_ray_on_sphere(
		t_scene const *scene,
		t_sphere const *sphere,
		t_ray const *ray,
		float distance)
{
	t_ray	normal;
	t_color	color;

	(void) scene;
	_compute_normal_ray(sphere, ray, distance, &normal);
	compute_illumination(scene, ray, &normal, &color);
	color.r *= sphere->color.r / 255.0f;
	color.g *= sphere->color.g / 255.0f;
	color.b *= sphere->color.b / 255.0f;
	DEBUG("color: %f %f %f\n", color.r, color.g, color.b);
	DEBUG("color: %X\n", color_to_int(&color));
	return (color_to_int(&color));
}

static void	_compute_normal_ray(
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
