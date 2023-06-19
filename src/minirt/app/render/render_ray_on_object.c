/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_ray_on_object.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouba <aderouba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 13:39:22 by tdubois           #+#    #+#             */
/*   Updated: 2023/06/19 15:20:55 by aderouba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt/app/app.h"

#include <stdint.h>
#include <stdio.h>

#include "minirt/app/app_config.h"
#include "minirt/app/utils/color/color.h"

static t_color	merge_color(
					t_object const *object,
					t_color const *in_color,
					t_color const *refracted_color,
					t_color const *reflected_color);

t_color	render_ray_on_object(
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
	// On merge la couleur avec l'illumination
	color.r = intersected_object->color.r * (illumination.r / 255.0f);
	color.g = intersected_object->color.g * (illumination.g / 255.0f);
	color.b = intersected_object->color.b * (illumination.b / 255.0f);

	refracted_color = compute_refracted_color(
			intersected_object, scene, ray, &normal);
	//TODO mirror here

	color = merge_color(intersected_object, &color,
				&refracted_color, &reflected_color);

	return (color);
}

static t_color	merge_color(
					t_object const *object,
					t_color const *in_color,
					t_color const *refracted_color,
					t_color const *reflected_color)
{
	t_color		color;
	float const	inv_opacity = 1.0f - object->opacity;
	// float const	inv_reflection = 1.0f - object->reflection;

	(void)reflected_color;
	color.r = (in_color->r * object->opacity)
			+ (refracted_color->r * inv_opacity);
	color.g = (in_color->g * object->opacity)
			+ (refracted_color->g * inv_opacity);
	color.b = (in_color->b * object->opacity)
			+ (refracted_color->b * inv_opacity);
	return (color);
}
