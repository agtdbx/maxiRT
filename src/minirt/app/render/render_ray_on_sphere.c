/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_ray_on_sphere.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdubois <tdubois@student.42angouleme.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 10:06:32 by tdubois           #+#    #+#             */
/*   Updated: 2023/06/02 04:24:01 by tdubois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt/app/app.h>

#include <minirt/scene/scene.h>
#include <minirt/utils/geometry.h>

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
	// float	intensity;
	t_color	illumination;

	(void) scene;
	_compute_normal_ray(sphere, ray, distance, &normal);
	//TODO compute illumination
	compute_illumination(scene, ray, &normal, &illumination);
	// intensity = -vec3_dot(&normal.vec, &ray->vec);
	return (255
		| ((int32_t)(sphere->color.r * illumination.r / 255 ) << 24)
		| ((int32_t)(sphere->color.g * illumination.g / 255 ) << 16)
		| ((int32_t)(sphere->color.b * illumination.b / 255 ) << 8));
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
