/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compute_illumination.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdubois <tdubois@student.42angouleme.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 02:23:39 by tdubois           #+#    #+#             */
/*   Updated: 2023/06/09 17:41:19 by tdubois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt/app/app.h"

#include <math.h>
#include <stddef.h>

#include "minirt/app/app_config.h"
#include "minirt/app/utils/geometry/geometry.h"
#include "minirt/debug/debug.h"//TODO debug

typedef struct s_phong_model
{
	t_ray const		*ray_from_camera;
	t_ray const		*ray_normal;
	t_light const	*spotlight;
}	t_phong_model;

static void	_collect_illumination_from_spotlight(
				t_scene const *scene,
				t_phong_model const *model,
				t_color *illumination);
static void	_collect_objects_shades(
				t_object const *objects,
				float dist_to_spotlight,
				t_ray const *ray_to_spotlight,
				t_color *illumination);

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
void	compute_illumination(
			t_scene const *scene,
			t_ray const *ray,
			t_ray const *normal,
			t_color *illumination)
{
	float			ambient_illumination;
	t_color			illumination_from_spotlight;
	t_phong_model	model;

	model.ray_normal = normal;
	model.ray_from_camera = ray;
	model.spotlight = scene->spotlights;
	ambient_illumination = 
		scene->ambient_lightning->brightness * g_ambient_reflection_constant;
	illumination->r = scene->ambient_lightning->color.r * ambient_illumination;
	illumination->g = scene->ambient_lightning->color.g * ambient_illumination;
	illumination->b = scene->ambient_lightning->color.b * ambient_illumination;
	while (model.spotlight != NULL)
	{
		_collect_illumination_from_spotlight(
				scene, &model, &illumination_from_spotlight);
		illumination->r += 
			illumination_from_spotlight.r * model.spotlight->color.r;
		illumination->g += 
			illumination_from_spotlight.g * model.spotlight->color.g;
		illumination->b += 
			illumination_from_spotlight.b * model.spotlight->color.b;
		model.spotlight = model.spotlight->next;
	}
}

#pragma clang diagnostic ignored "-Wunused-parameter"

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
					t_scene const *scene,
					t_phong_model const *model,
					t_color *illumination)
{
	float			dist_to_spotlight;
	t_ray			ol;
	t_vec3			os;
	float			idiffuse;
	float			ispecular;

	vec3_substract_into(&ol.vec, &model->spotlight->pos, &model->ray_normal->pos);
	dist_to_spotlight = vec3_normalize(&ol.vec);
	idiffuse = vec3_dot(&model->ray_normal->vec, &ol.vec);
	*illumination = (t_color){0};
	if (idiffuse <= 0.0f)
		return ;
	*illumination = (t_color){1.0f, 1.0f, 1.0f};
	ol.pos = model->ray_normal->pos;
	_collect_objects_shades(scene->objects, dist_to_spotlight, &ol, illumination);
	if (illumination->r == 0.0f
			&& illumination->g == 0.0f 
			&& illumination->b == 0.0f)
		return ;
	vec3_linear_transform(&os, 2.0f * idiffuse, &model->ray_normal->vec);
	vec3_substract(&os, &ol.vec);
	vec3_normalize(&os);
	idiffuse *= g_diffuse_reflection_constant;
	ispecular = fmaxf(0.0f, -vec3_dot(&os, &model->ray_from_camera->vec));
	ispecular = powf(ispecular, g_phong_exponent) * g_specular_reflection_constant;
	color_scale(
		illumination, (idiffuse + ispecular) * model->spotlight->brightness);
}

t_color const	*obj_get_color(
					t_object const *object)
{
	if (object->type == OBJ_SPHERE)
		return (&object->value.as_sphere.color);
	return (NULL);
}

float	obj_get_opacity(
			t_object const *object)
{
	if (object->type == OBJ_SPHERE)
		return (object->value.as_sphere.opacity);
	return (1.0f);
}

static bool	_test_intersection(
				t_ray const *ray,
				t_object const *object,
				float *distance)
{
	if (object->type == OBJ_SPHERE)
		return (test_intersection_with_sphere(
					ray, &object->value.as_sphere, distance));
	return (false);
}

static void	_collect_objects_shades(
				t_object const *objects,
				float dist_to_spotlight,
				t_ray const *ray_to_spotlight,
				t_color *illumination)
{
	float			distance_to_object;
	t_color const	*obj_color;
	float			obj_opacity;

	while (objects != NULL)
	{
		if (_test_intersection(ray_to_spotlight, objects, &distance_to_object)
			&& (distance_to_object < dist_to_spotlight))
		{
			obj_color = obj_get_color(objects);
			obj_opacity = obj_get_opacity(objects);
			illumination->r -= obj_opacity + obj_opacity * ((128 - obj_color->r) / 255.0f);
			illumination->g -= obj_opacity + obj_opacity * ((128 - obj_color->g) / 255.0f);;
			illumination->b -= obj_opacity + obj_opacity * ((128 - obj_color->b) / 255.0f);;
			DEBUG_COLORP(illumination);
		}
		if (illumination->r == 0.0f
				&& illumination->g == 0.0f 
				&& illumination->b == 0.0f)
			return ;
		objects = objects->next;
	}
}

			// illumination->r *= 1.0f - (obj_color->r / 255.0f) * obj_opacity;
			// illumination->g *= 1.0f - (obj_color->g / 255.0f) * obj_opacity;
			// illumination->b *= 1.0f - (obj_color->b / 255.0f) * obj_opacity;

