/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_ray_on_object.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouba <aderouba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 13:39:22 by tdubois           #+#    #+#             */
/*   Updated: 2023/06/15 13:22:59 by aderouba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt/app/app.h"

#include <stdint.h>

#include "minirt/app/app_config.h"
#include "minirt/app/utils/color/color.h"

static void	_compute_normal_ray_on_sphere(
				t_sphere const *sphere,
				t_ray const *ray,
				float distance,
				t_ray *normal);


int32_t	render_ray_on_object(
			t_scene const *scene,
			t_object const	*intersected_object,
			t_ray const *ray,
			float distance)
{
	t_ray	normal;
	t_color	illumination;
	// t_color	refracted_color;
	t_color	color;

	if (intersected_object->type == OBJ_SPHERE)
		_compute_normal_ray_on_sphere(&intersected_object->value.as_sphere, ray, distance, &normal);
	else
		return (g_color_black);
	//TODO normal mapping here
	compute_illumination(scene, ray, &normal, &illumination);
	// compute_refracted_color(scene, ray, &normal, &refracted_color);
	//TODO mirror here
	// color = refracted_color;
	color = illumination;
	color.r *= intersected_object->color.r / 255.0f;
	color.g *= intersected_object->color.g / 255.0f;
	color.b *= intersected_object->color.b / 255.0f;
	return (color_to_int(&color));
}

static void	_compute_normal_ray_on_sphere(
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
