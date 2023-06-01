/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_ray.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdubois <tdubois@student.42angouleme.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 08:17:25 by tdubois           #+#    #+#             */
/*   Updated: 2023/06/01 13:58:01 by tdubois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt/app/app.h>

#include <minirt/scene/scene.h>
#include <minirt/utils/color.h>
#include <stdbool.h>
#include <stdbool.h>
#include <stdio.h>

typedef struct s_intersection
{
	t_object const	*object;
	float			distance;

	t_vec3			pos;
	t_vec3			normal;
}	t_intersection;

////////////////////////////////////////////////////////////////////////////////

static t_light const	*_fetch_closer_spotlight(
							t_ray const *ray,
							t_light const *lights,
							float *distance);
static int32_t			_render_ray_on_spotlight(
							t_light const *light,
							t_ray const *ray,
							float distance);
static inline float		_apply_fish_eye_effect_correction(
							float initial_distance,
							t_vec3 const *camera_direction,
							t_vec3 const *ray_direction);

int32_t	render_ray_from_camera(
			t_scene const *scene,
			t_ray const *ray,
			bool show_spotlights)
{
	t_object const	*intersected_object;
	t_light const	*light;
	float			distance;

	intersected_object = 
		fetch_closest_intersection(ray, scene->objects, &distance);
	if (show_spotlights)
	{
		light = _fetch_closer_spotlight(ray, scene->spotlights, &distance);
		if (light != NULL)
			return (_render_ray_on_spotlight(light, ray, distance));
	}
	if (intersected_object == NULL)
		return (RGB_BLACK);
	distance = _apply_fish_eye_effect_correction(
		distance, &scene->camera->direction, &ray->vec);
	return (render_ray_on_object(scene, intersected_object, ray, distance));
}

static t_light const	*_fetch_closer_spotlight(
							t_ray const *ray,
							t_light const *lights,
							float *distance)
{
	float			actual_distance;
	t_light const	*intersected_light;
	t_sphere		light_bulb;

	light_bulb.radius = 0.1;
	light_bulb.radius2 = 0.01;
	intersected_light = NULL;
	while (lights != NULL)
	{
		light_bulb.pos = lights->pos;
		if (test_intersection_with_sphere(ray, &light_bulb, &actual_distance)
			&& !(0 <= *distance && *distance <= actual_distance))
		{
			*distance = actual_distance;
			intersected_light = lights;
		}
		lights = lights->next;
	}
	return (intersected_light);
}

static int32_t	_render_ray_on_spotlight(
					t_light const *light,
					t_ray const *ray,
					float distance)
{
	t_ray	normal;
	float	intensity;

	normal.pos = ray->pos;
	vec3_linear_transform(&normal.pos, distance, &ray->vec);
	vec3_substract_into(&normal.vec, &normal.pos, &light->pos);
	vec3_normalize(&normal.vec);

	intensity = -vec3_dot(&normal.vec, &ray->vec);
	if (intensity < 0.3)
		return (0xFFFFFFFF);
	else if (intensity < 0.6)
		return (0xFF);
	return (255
		| ((int32_t)(light->color.r * light->brightness) << 24)
		| ((int32_t)(light->color.g * light->brightness) << 16)
		| ((int32_t)(light->color.b * light->brightness) << 8));
}

static inline float	_apply_fish_eye_effect_correction(
						float initial_distance,
						t_vec3 const *camera_direction,
						t_vec3 const *ray_direction)
{
	return (0.0f
		+ camera_direction->x * ray_direction->x * initial_distance
		+ camera_direction->y * ray_direction->y * initial_distance
		+ camera_direction->z * ray_direction->z * initial_distance);
}
