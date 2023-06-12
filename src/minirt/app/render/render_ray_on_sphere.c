/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_ray_on_sphere.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdubois <tdubois@student.42angouleme.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 10:06:32 by tdubois           #+#    #+#             */
/*   Updated: 2023/06/12 17:16:13 by tdubois          ###   ########.fr       */
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
	t_color	illumination;
	// t_color	refracted_color;
	t_color	color;

	_compute_normal_ray(sphere, ray, distance, &normal);
	//TODO normal mapping here
	compute_illumination(scene, ray, &normal, &illumination);
	// compute_refracted_color(scene, ray, &normal, &refracted_color);
	//TODO mirror here
	// color = refracted_color;
	color = illumination;
	color.r *= sphere->color.r / 255.0f;
	color.g *= sphere->color.g / 255.0f;
	color.b *= sphere->color.b / 255.0f;
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
