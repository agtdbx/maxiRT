/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_ray_on_object.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdubois <tdubois@student.42angouleme.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 13:39:22 by tdubois           #+#    #+#             */
/*   Updated: 2023/06/12 17:37:32 by tdubois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt/app/app.h"

#include <stdint.h>

#include "minirt/app/app_config.h"
#include "minirt/app/utils/color/color.h"

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

	compute_normal_ray(intersected_object, ray, distance, &normal);
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
