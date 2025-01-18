/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_ray_from_camera.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gugus <gugus@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 12:44:01 by tdubois           #+#    #+#             */
/*   Updated: 2024/06/16 16:11:33 by gugus            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt/app/app.h"

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <time.h>
#include <stdlib.h>

#include "minirt/app/app_config.h"
#include "minirt/app/scene/scene.h"
#include "minirt/app/utils/color/color.h"

#define X 0
#define Y 1

static bool	blinded_lights = true;

static int32_t	_render_ray_on_spotlight(
					t_light const *light,
					t_ray const *ray,
					t_intersect_info const *intersect_info);

/**
 * @param[in] scene
 * @param[in] ray Normalized ray from camera
 * @param[in] show_spotlights Wether to render spotlight as disks.
 * @return color The resulting color
 */
int32_t	render_ray_from_camera(
			t_task *task,
			t_scene const *scene,
			pthread_rwlock_t *scene_mut,
			bool show_spotlights)
{
	t_object const		*intersected_object;
	t_light const		*light;
	t_color				pixel_color;
	t_color				blinded_color;
	t_intersect_info	intersect_info;

	pthread_rwlock_rdlock(scene_mut);
	intersected_object = fetch_closest_intersection(
							&task->ray, scene->objects, &intersect_info);
	pthread_rwlock_unlock(scene_mut);
	if (show_spotlights)
	{
		light = fetch_closer_spotlight(
				&task->ray, scene->spotlights, &intersect_info);
		if (light != NULL)
			return (_render_ray_on_spotlight(light, &task->ray, &intersect_info));
	}
	if (intersected_object == NULL)
	{
		pixel_color = (t_color){0};
		if (scene->skybox)
			pixel_color = render_ray_on_sky_box(scene, &task->ray);

		if (!show_spotlights && blinded_lights)
		{
			blinded_color = compute_blinded_illumination(scene, &task->ray);
			pixel_color.r += blinded_color.r;
			if (pixel_color.r > 255.0f)
				pixel_color.r = 255.0f;
			pixel_color.g += blinded_color.g;
			if (pixel_color.g > 255.0f)
				pixel_color.g = 255.0f;
			pixel_color.b += blinded_color.b;
			if (pixel_color.b > 255.0f)
				pixel_color.b = 255.0f;
		}
	}
	else
		pixel_color = render_ray_on_object(
						scene, intersected_object, &task->ray, &intersect_info);


	pixel_color.r *= scene->color_filter.x;
	pixel_color.g *= scene->color_filter.y;
	pixel_color.b *= scene->color_filter.z;

	return (color_to_int(&pixel_color));
}

static int32_t	_render_ray_on_spotlight(
					t_light const *light,
					t_ray const *ray,
					t_intersect_info const *intersect_info)
{
	t_ray	normal;
	float	intensity;
	t_color	color;

	normal.pos = ray->pos;
	vec3_linear_transform(&normal.pos, intersect_info->distance, &ray->vec);
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
