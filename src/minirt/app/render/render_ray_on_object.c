/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_ray_on_object.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouba <aderouba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 13:39:22 by tdubois           #+#    #+#             */
/*   Updated: 2023/06/19 11:48:31 by aderouba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt/app/app.h"

#include <stdint.h>

#include "minirt/app/app_config.h"
#include "minirt/app/utils/color/color.h"

static t_color	merge_color(
					t_object const *object,
					t_color const *refracted_color,
					t_color const *reflected_color);

int32_t	render_ray_on_object(
			t_scene const *scene,
			t_object const *intersected_object,
			t_ray const *ray,
			float distance)
{
	t_ray	normal;
	t_color	illumination;
	t_color	refracted_color;
	t_color	reflected_color = { 0 };
	t_color	color;

	compute_normal_ray(intersected_object, ray, distance, &normal);
	//TODO normal mapping here
	compute_illumination(scene, ray, &normal, &illumination);
	refracted_color = compute_refracted_color(
			intersected_object, scene, ray, &normal);
	color = merge_color(intersected_object,
				&refracted_color, &reflected_color);
	//TODO mirror here

	// On merge la couleur avec l'illumination
	color.r *= illumination.r / 255.0f;
	color.g *= illumination.g / 255.0f;
	color.b *= illumination.b / 255.0f;
	return (color_to_int(&color));
}

static t_color	merge_color(
					t_object const *object,
					t_color const *refracted_color,
					t_color const *reflected_color)
{
	t_color		color;
	float const	inv_opacity = 1.0f - object->opacity;
	// float const	inv_reflection = 1.0f - object->reflection;

	(void)reflected_color;
	color.r = (object->color.r * object->opacity)
			+ (refracted_color->r * inv_opacity);
	color.g = (object->color.g * object->opacity)
			+ (refracted_color->g * inv_opacity);
	color.b = (object->color.b * object->opacity)
			+ (refracted_color->b * inv_opacity);
	return (color);
}
