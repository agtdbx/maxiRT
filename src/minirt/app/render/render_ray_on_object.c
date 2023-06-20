/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_ray_on_object.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouba <aderouba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 13:39:22 by tdubois           #+#    #+#             */
/*   Updated: 2023/06/20 19:54:57 by aderouba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt/app/app.h"

#include <stdint.h>

#include "minirt/app/app_config.h"
#include "minirt/app/utils/color/color.h"

static t_color	get_base_color_object(
			t_object const *intersected_object);
static t_color	compute_object_without_effect_color(
			t_object const *intersected_object,
			t_scene const *scene,
			t_ray const *ray,
			t_ray const *normal);
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
	t_color	refracted_color;
	t_color	reflected_color;
	t_color	color;

	compute_normal_ray(intersected_object, ray, distance, &normal);
	//TODO normal mapping here

	color = compute_object_without_effect_color(
			intersected_object, scene, ray, &normal);
	refracted_color = compute_refracted_color(
			intersected_object, scene, ray, &normal);
	reflected_color = compute_reflected_color(
			intersected_object, scene, ray, &normal);

	color = merge_color(intersected_object, &color,
				&refracted_color, &reflected_color);
	return (color);
}

// Retourne la couleur de l'objet sans la transparence et le reflet ni la lumière
static t_color	get_base_color_object(
			t_object const *intersected_object)
{
	t_color	base_color;

	// TODO Texturing here
	base_color = intersected_object->color;
	return (base_color);
}

// Retourne la couleur de l'objet sans la transparence et le reflet
static t_color	compute_object_without_effect_color(
			t_object const *intersected_object,
			t_scene const *scene,
			t_ray const *ray,
			t_ray const *normal)
{
	t_color	illumination;
	t_color	base_color;
	t_color	color;

	illumination = compute_illumination(
			scene, intersected_object, ray, normal);
	// On récupère la couleur de l'objet
	base_color = get_base_color_object(intersected_object);
	// On applique l'illumination à la couleur
	color.r = intersected_object->color.r * (illumination.r / 255.0f);
	color.g = intersected_object->color.g * (illumination.g / 255.0f);
	color.b = intersected_object->color.b * (illumination.b / 255.0f);
	return (color);
}

// Merge les couleurs
static t_color	merge_color(
					t_object const *object,
					t_color const *in_color,
					t_color const *refracted_color,
					t_color const *reflected_color)
{
	t_color		color;
	float const	inv_opacity = 1.0f - object->opacity;
	float const	inv_reflection = 1.0f - object->reflection;

	color = *in_color;
	if (object->opacity < 1.0f)
	{
		color.r = (color.r * object->opacity)
			+ (refracted_color->r * inv_opacity);
		color.g = (color.g * object->opacity)
			+ (refracted_color->g * inv_opacity);
		color.b = (color.b * object->opacity)
			+ (refracted_color->b * inv_opacity);
	}
	if (object->reflection > 0.0f)
	{
		color.r = (color.r * inv_reflection)
			+ (reflected_color->r * object->reflection);
		color.g = (color.g * inv_reflection)
			+ (reflected_color->g * object->reflection);
		color.b = (color.b * inv_reflection)
			+ (reflected_color->b * object->reflection);
	}
	return (color);
}
