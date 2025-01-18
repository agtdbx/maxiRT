/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_ray_on_object.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gugus <gugus@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 13:39:22 by tdubois           #+#    #+#             */
/*   Updated: 2024/06/16 16:11:43 by gugus            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt/app/app.h"

#include <stdint.h>

#include "minirt/app/app_config.h"
#include "minirt/app/utils/color/color.h"

static t_pixel_info	get_pixel_info(
						t_scene const *scene,
						t_object const *intersected_object,
						t_ray const *ray,
						t_intersect_info const *intersect_info);

static t_color		compute_object_without_effect_color(
						t_object const *intersected_object,
						t_scene const *scene,
						t_ray const *ray,
						t_pixel_info const *pixel_info);

static t_color		merge_color(
						t_object const *object,
						t_color const *in_color,
						t_color const *refracted_color,
						t_color const *reflected_color,
						bool force_transparency);

t_color	render_ray_on_object(
			t_scene const *scene,
			t_object const *intersected_object,
			t_ray const *ray,
			t_intersect_info const *intersect_info)
{
	t_pixel_info	pixel_info;
	t_color			refracted_color;
	t_color			reflected_color;
	t_color			color;
	bool			force_transparency;

	if (ray->depth > 16)
		return ((t_color){0});
	pixel_info = get_pixel_info(scene, intersected_object, ray, intersect_info);
	color = compute_object_without_effect_color(
				intersected_object, scene, ray, &pixel_info);
	force_transparency = false;
	if (color.a == -1.0f)
		force_transparency = true;
	refracted_color = compute_refracted_color(
			intersected_object, scene, ray, &pixel_info.normal, force_transparency);
	reflected_color = compute_reflected_color(
			intersected_object, scene, ray, &pixel_info.normal);
	color = merge_color(intersected_object, &color,
							&refracted_color, &reflected_color,
							force_transparency);

	if (scene->blinded_lights)
		apply_blinded_illumination(scene, ray, &color);
	return (color);
}

static t_pixel_info	get_pixel_info(
						t_scene const *scene,
						t_object const *intersected_object,
						t_ray const *ray,
						t_intersect_info const *intersect_info)
{
	t_pixel_info	pixel_info;
	t_ray			normal_from_map;
	t_color			illumination;

	compute_normal_ray(
		intersected_object, ray, intersect_info, &pixel_info.normal);
	pixel_info.pos = get_object_pixel_pos(
			intersected_object, ray, &pixel_info.normal, intersect_info);
	normal_from_map = pixel_info.normal;
	compute_normal_map(
		intersected_object, intersect_info, &pixel_info.pos, &normal_from_map);
	if (pixel_info.normal.vec.x != normal_from_map.vec.x
		|| pixel_info.normal.vec.y != normal_from_map.vec.y
		|| pixel_info.normal.vec.z != normal_from_map.vec.z)
	{
		illumination = check_dynamic_illumination(
				scene, intersected_object, ray, &pixel_info.normal);
		if (illumination.r != 0.0f || illumination.g != 0.0f
			|| illumination.g != 0.0f)
			pixel_info.normal = normal_from_map;
	}
	return (pixel_info);
}

static t_color	compute_object_without_effect_color(
					t_object const *intersected_object,
					t_scene const *scene,
					t_ray const *ray,
					t_pixel_info const *pixel_info)
{
	t_color	illumination;
	t_color	base_color;
	t_color	color;

	base_color = get_base_color_object(intersected_object, &pixel_info->pos);
	illumination = compute_illumination(
			scene, intersected_object, ray, &pixel_info->normal);
	if (illumination.r == 0.0f && illumination.g == 0.0f
		&& illumination.g == 0.0f)
		return (illumination);
	color.r = base_color.r * (illumination.r / 255.0f);
	color.g = base_color.g * (illumination.g / 255.0f);
	color.b = base_color.b * (illumination.b / 255.0f);
	color.a = base_color.a;
	return (color);
}

static t_color	merge_color(
					t_object const *object,
					t_color const *in_color,
					t_color const *refracted_color,
					t_color const *reflected_color,
					bool force_transparency)
{
	t_color		color;
	float const	inv_opacity = 1.0f - object->opacity;
	float const	inv_reflection = 1.0f - object->reflection;

	if (force_transparency)
		return (*refracted_color);
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
