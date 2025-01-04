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

#define SAMPLE_SIZE 9

static int32_t	_render_ray_on_spotlight(
					t_light const *light,
					t_ray const *ray,
					t_intersect_info const *intersect_info);

static inline int32_t	_fetch_intersection_with_skybox(
			t_canvas *canvas,
			int *pixels,
			t_scene const *scene,
			t_ray const *ray,
			t_object const *skybox,
			t_intersect_info *intersect_info);
/**
 * @param[in] scene
 * @param[in] ray Normalized ray from camera
 * @param[in] show_spotlights Wether to render spotlight as disks.
 * @return color The resulting color
 */
int32_t	render_ray_from_camera(
			t_canvas *canvas,
			t_task *task,
			t_scene const *scene,
			pthread_rwlock_t *scene_mut,
			t_ray const *ray,
			bool show_spotlights)
{
	t_object const		*intersected_object;
	t_light const		*light;
	t_color				pixel_color;
	t_intersect_info	intersect_info;

	pthread_rwlock_rdlock(scene_mut);
	intersected_object = fetch_closest_intersection_in_tree(
							ray, scene, &intersect_info);
	pthread_rwlock_unlock(scene_mut);
	if (show_spotlights)
	{
		light = fetch_closer_spotlight(
				ray, scene->spotlights, &intersect_info);
		if (light != NULL)
			return (_render_ray_on_spotlight(light, ray, &intersect_info));
	}
	if (intersected_object == NULL)
	{
		if (scene->skybox)
			return _fetch_intersection_with_skybox(canvas, task->pixels, scene, ray,
				scene->skybox, &intersect_info);
		return (g_color_black);
	}
	pixel_color = render_ray_on_object(
			scene, intersected_object, ray, &intersect_info);
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

static t_color	sample_color_around_pixel(const t_scene *scene, t_canvas *canvas,
	const t_object *skybox, t_intersect_info *intersect_info, int *pixels)
{
	int		i;
	double	random;
	double	neighbours_pixel[2];
	t_color	samples_colors[SAMPLE_SIZE] = {{0, 0, 0}};
	t_color	average_color = {0, 0, 0};
	t_ray	new_ray;
	int		effective_sample_size;

	effective_sample_size = SAMPLE_SIZE;
	for (i = 0; i < SAMPLE_SIZE; i++)
	{
		random = ((double)rand() / (double)RAND_MAX) * 2.0 - 1.0;
		neighbours_pixel[0] = (pixels[0] /+ random);
		random = ((double)rand() / (double)RAND_MAX) * 2.0f - 1.0;
		neighbours_pixel[1] = (pixels[1] + random);

		new_ray = create_ray_from_pixel_coords(scene->camera, canvas, neighbours_pixel);
		new_ray.depth = 0;
		if (!test_intersection_with_cube_from_inside(
			&new_ray, &skybox->value.as_skybox.cube, intersect_info))
		{
			effective_sample_size--;
			continue ;
		}
		samples_colors[i] = render_ray_on_object(scene, skybox,
			&new_ray, intersect_info);
	}
	for (i = 0; i < SAMPLE_SIZE; i++)
	{
		average_color.r += samples_colors[i].r;
		average_color.g += samples_colors[i].g;
		average_color.b += samples_colors[i].b;
	}
	average_color.r /= effective_sample_size;
	average_color.g /= effective_sample_size;
	average_color.b /= effective_sample_size;
	return average_color;
}

static inline int32_t	_fetch_intersection_with_skybox(
			t_canvas *canvas,
			int *pixels,
			t_scene const *scene,
			t_ray const *ray,
			t_object const *skybox,
			t_intersect_info *intersect_info)
{
	t_color		pixel_color = {0, 0, 0};
	t_color		sample_color = {0, 0, 0};
	
	sample_color = sample_color_around_pixel(scene, canvas, skybox, intersect_info, pixels);
	if (!test_intersection_with_cube_from_inside(
			ray, &skybox->value.as_skybox.cube, intersect_info))
		return (color_to_int(&sample_color));
	pixel_color = render_ray_on_object(scene, skybox, ray, intersect_info);
	pixel_color.r = (pixel_color.r +  sample_color.r) / 2;
	pixel_color.g = (pixel_color.g +  sample_color.g) / 2;
	pixel_color.b = (pixel_color.b +  sample_color.b) / 2;
	return (color_to_int(&pixel_color));
}
