/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_ray_from_camera.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdubois <tdubois@student.42angouleme.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 18:10:35 by tdubois           #+#    #+#             */
/*   Updated: 2023/06/23 16:54:57 by tdubois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt/app/app.h"

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

#include "minirt/app/app_config.h"
#include "minirt/app/scene/scene.h"
#include "minirt/app/utils/color/color.h"

static int32_t			_render_ray_on_spotlight(
							t_light const *light,
							t_ray const *ray,
							float distance);

/**
 * @param[in] scene
 * @param[in] ray Normalized ray from camera
 * @param[in] show_spotlights Wether to render spotlight as disks.
 * @return color The resulting color
 */
int32_t	render_ray_from_camera(
			t_scene const *scene,
			t_ray const *ray,
			bool show_spotlights)
{
	t_object const	*intersected_object;
	t_light const	*light;
	t_color			pixel_color;
	float			distance;

	intersected_object = \
		fetch_closest_intersection(ray, scene->objects, &distance);
	if (show_spotlights)
	{
		light = fetch_closer_spotlight(ray, scene->spotlights, &distance);
		if (light != NULL)
			return (_render_ray_on_spotlight(light, ray, distance));
	}
	if (intersected_object == NULL)
		return (g_color_black);
	pixel_color =
		render_ray_on_object(scene, intersected_object, ray, distance);
	return (color_to_int(&pixel_color));
}

static int32_t	_render_ray_on_spotlight(
					t_light const *light,
					t_ray const *ray,
					float distance)
{
	t_ray	normal;
	float	intensity;
	t_color	color;

	normal.pos = ray->pos;
	vec3_linear_transform(&normal.pos, distance, &ray->vec);
	vec3_substract_into(&normal.vec, &normal.pos, &light->pos);
	vec3_normalize(&normal.vec);
	intensity = -vec3_dot(&normal.vec, &ray->vec);
	if (intensity < 0.3)
		return (0xFFFFFFFF);
	else if (intensity < 0.6)
		return (0xFF);
	color.r = light->color.r * light->brightness;
	color.g = light->color.g * light->brightness;
	color.b = light->color.b * light->brightness;
	return (color_to_int(&color));
}
