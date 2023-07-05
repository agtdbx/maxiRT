/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_ray_from_camera.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouba <aderouba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 18:10:35 by tdubois           #+#    #+#             */
/*   Updated: 2023/07/05 20:12:03 by aderouba         ###   ########.fr       */
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

static t_light const	*_fetch_closer_spotlight(
							t_ray const *ray,
							t_light const *lights,
							t_intersect_info *intersect_info);
static int32_t			_render_ray_on_spotlight(
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
			t_scene const *scene,
			t_ray const *ray,
			bool show_spotlights)
{
	t_object const		*intersected_object;
	t_light const		*light;
	t_color				pixel_color;
	t_intersect_info	intersect_info;

	intersected_object = \
		fetch_closest_intersection(ray, scene->objects, &intersect_info);
	if (show_spotlights)
	{
		light = _fetch_closer_spotlight(
				ray, scene->spotlights, &intersect_info);
		if (light != NULL)
			return (_render_ray_on_spotlight(light, ray, &intersect_info));
	}
	if (intersected_object == NULL)
		return (g_color_black);
	pixel_color = render_ray_on_object(
			scene, intersected_object, ray, &intersect_info);
	return (color_to_int(&pixel_color));
}

static t_light const	*_fetch_closer_spotlight(
							t_ray const *ray,
							t_light const *lights,
							t_intersect_info *intersect_info)
{
	t_intersect_info	actual_intersect_info;
	t_light const		*intersected_light;
	t_sphere			light_bulb;

	light_bulb.radius = 0.1;
	light_bulb.radius2 = 0.01;
	intersected_light = NULL;
	while (lights != NULL)
	{
		light_bulb.pos = lights->pos;
		if (test_intersection_with_sphere(
				ray, &light_bulb, &actual_intersect_info)
			&& !(0 <= intersect_info->distance && intersect_info->distance
				<= actual_intersect_info.distance))
		{
			intersect_info->distance = actual_intersect_info.distance;
			intersected_light = lights;
		}
		lights = lights->next;
	}
	return (intersected_light);
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
