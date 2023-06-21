/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compute_illumination.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouba <aderouba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 02:23:39 by tdubois           #+#    #+#             */
/*   Updated: 2023/06/21 11:44:05 by aderouba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt/app/app.h"

#include <math.h>
#include <stddef.h>

#include "minirt/app/app_config.h"
#include "minirt/app/utils/geometry/geometry.h"
#include <minirt/app/scene/scene.h>

#include "minirt/debug/debug.h"//TODO debug

static void		_collect_illumination_from_spotlight(
					t_object const *objects,
					t_object const *object,
					t_phong_model const *model,
					t_color *illumination,
				t_color const *base_color);
static t_color	_collect_objects_shades(
				t_object const *objects,
				t_object const *object,
				float dist_to_spotlight,
				t_ray const *ray_to_spotlight,
				t_color const *base_color);

/**
 * Compute illumination of point normal->pos
 * according to PHONG illumination model.
 *
 * I(llumination) = Iambient + Sum( (Idiffuse + Ispecular) * brightness)
 *
 * @param[in] scene
 * @param[in] ray
 * @param[in] normal
 * @param[out] illumination
 */
t_color	compute_illumination(
			t_scene const *scene,
			t_object const *object,
			t_ray const *ray,
			t_ray const *normal,
			t_color const *base_color)
{
	float			ambient_illumination;
	t_color			illumination_from_spotlight;
	t_phong_model	model;
	t_color			illumination;

	model.normal = normal;
	model.from_camera = ray;
	model.spotlight = scene->spotlights;
	ambient_illumination =
		scene->ambient_lightning->brightness * g_ambient_light_ratio;
	illumination.r = scene->ambient_lightning->color.r * ambient_illumination;
	illumination.g = scene->ambient_lightning->color.g * ambient_illumination;
	illumination.b = scene->ambient_lightning->color.b * ambient_illumination;
	while (model.spotlight != NULL)
	{
		illumination_from_spotlight = (t_color){ 0 };
		_collect_illumination_from_spotlight(
				scene->objects, object, &model, &illumination_from_spotlight, base_color);
		illumination.r +=
			illumination_from_spotlight.r * model.spotlight->color.r;
		illumination.g +=
			illumination_from_spotlight.g * model.spotlight->color.g;
		illumination.b +=
			illumination_from_spotlight.b * model.spotlight->color.b;
		model.spotlight = model.spotlight->next;
	}
	return (illumination);
}

/**
 * compute_illumination from a single spotlight
 *
 * C: camera
 * L: light source
 * T: tangent plane
 * N: normal vector
 *
 * S: symetric of L with respect to N
 *
 *               N
 *    S     C    |          L
 *     \__   \   |       __/
 *        \__ \  |    __/
 *           \_\ | __/
 *              \|/
 * --------------O--------------- T
 *
 * I(llumination) = Idiffuse + Ispecular
 *
 * OS = 2 * (ON.OL) * ON - OL
 *
 * Idiffuse  = ON.OL
 * Ispecular = OS.OC
 *
 * @param[in] scene
 * @param[in] ray
 * @param[in] normal
 * @param[in] spotlight
 * @returns illumination
 */
static void	_collect_illumination_from_spotlight(
					t_object const *objects,
					t_object const *object,
					t_phong_model const *model,
					t_color *illumination,
					t_color const *base_color)
{
	float			dist_to_spotlight;
	t_ray			ol;
	t_vec3			os;
	float			idiffuse;
	float			ispecular;

	vec3_substract_into(&ol.vec, &model->spotlight->pos, &model->normal->pos);
	dist_to_spotlight = vec3_normalize(&ol.vec);
	idiffuse = vec3_dot(&model->normal->vec, &ol.vec);
	if (idiffuse <= 0.0f)
		return ;
	ol.pos = model->normal->pos;
	*illumination = _collect_objects_shades(objects, object,
		dist_to_spotlight, &ol, base_color);
	if (illumination->r <= 0.0f && illumination->g <= 0.0f
		&& illumination->b <= 0.0f)
	{
		*illumination = (t_color){ 0 };
		return ;
	}
	os = (t_vec3){ 0 };
	vec3_linear_transform(&os, 2.0f * idiffuse, &model->normal->vec);
	vec3_substract(&os, &ol.vec);
	vec3_normalize(&os);
	idiffuse *= g_diffuse_light_ratio;
	ispecular = fmaxf(0.0f, -vec3_dot(&os, &model->from_camera->vec));
	ispecular = powf(ispecular, g_phong_exponent) * g_specular_light_ratio;
	color_scale(
		illumination, (idiffuse + ispecular) * model->spotlight->brightness);
	DEBUG_COLORP(illumination);
}

static t_color	_collect_objects_shades(
				t_object const *objects,
				t_object const *object,
				float dist_to_spotlight,
				t_ray const *ray_to_spotlight,
				t_color const *base_color)
{
	float	distance_to_object;
	t_color illumination;

	illumination = (t_color){1.0f, 1.0f, 1.0f};
	while (objects != NULL)
	{
		if (objects != object
			&& test_intersection_with_obj(
				ray_to_spotlight, objects, &distance_to_object)
			&& (distance_to_object < dist_to_spotlight))
		{
			illumination.r -= powf(objects->opacity,
					1 + base_color->r * g_opacity_color_ratio);
			illumination.g -= powf(objects->opacity,
					1 + base_color->g * g_opacity_color_ratio);
			illumination.b -= powf(objects->opacity,
					1 + base_color->b * g_opacity_color_ratio);
		}
		if (illumination.r <= 0.0f
				&& illumination.g <= 0.0f
				&& illumination.b <= 0.0f)
			return (illumination);
		objects = objects->next;
	}
	return (illumination);
}
