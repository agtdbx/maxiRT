/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_ray.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdubois <tdubois@student.42angouleme.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 08:17:25 by tdubois           #+#    #+#             */
/*   Updated: 2023/05/16 14:05:16 by tdubois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt/app/app.h>

#include <minirt/scene/scene.h>
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

#define RGB_BLACK 0x000000FF

static inline float	_apply_fish_eye_effect_correction(
						float initial_distance,
						t_vec3 const *camera_direction,
						t_vec3 const *ray_direction);

int	render_ray(
		t_scene const *scene,
		t_ray const *ray)
{
	t_object const	*intersected_object;
	float			distance;

	intersected_object = 
		fetch_closest_intersection(ray, scene->objects, &distance);
	if (intersected_object == NULL)
		return (RGB_BLACK);
	distance = _apply_fish_eye_effect_correction(
		distance, &scene->camera->direction, &ray->vec);
	if (intersected_object->type == OBJ_SPHERE)
		return (render_ray_on_sphere(
			(t_sphere*)&intersected_object->value, ray, distance));
	//other object types...
	return (RGB_BLACK);
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
