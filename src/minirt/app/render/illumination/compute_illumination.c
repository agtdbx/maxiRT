/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compute_illumination.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdubois <tdubois@student.42angouleme.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 02:23:39 by tdubois           #+#    #+#             */
/*   Updated: 2023/06/05 15:29:42 by tdubois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt/app/app.h>

#include <minirt/debug/debug.h>//TODO debug
#include <minirt/utils/geometry.h>
#include <math.h>

#define AMBIENT_REFLECTION_CONSTANT 0.3f
#define DIFFUSE_REFLECTION_CONSTANT 0.3f
#define SPECULAR_REFLECTION_CONSTANT 0.3f
#define PHONG_EXPONENT 50.0f

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
static bool		_is_spotlight_behind_object(
					t_scene const *scene,
					float dist_to_spotlight,
					t_ray const *ray_toward_spotlight);

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
// void	compute_illumination(
// 			t_scene const *scene,
// 			t_ray const *ray,
// 			t_ray const *normal,
// 			t_color *illumination)
// {
// 	t_light const	*spotlight;
// 	float			illumination_from_spotlight;
// 	float			Iambient;
//
// 	Iambient =
// 		scene->ambient_lightning->brightness * AMBIENT_REFLECTION_CONSTANT;
// 	illumination->r = scene->ambient_lightning->color.r * Iambient;
// 	illumination->g = scene->ambient_lightning->color.g * Iambient;
// 	illumination->b = scene->ambient_lightning->color.b * Iambient;
// 	spotlight = scene->spotlights;
// 	while (spotlight != NULL)
// 	{
// 		illumination_from_spotlight = _compute_illumination_from_spotlight(
// 				scene, ray, normal, spotlight);
// 		if (illumination_from_spotlight > 0.0f)
// 		{
// 			illumination->r += spotlight->color.r * illumination_from_spotlight;
// 			illumination->g += spotlight->color.g * illumination_from_spotlight;
// 			illumination->b += spotlight->color.b * illumination_from_spotlight;
// 		}
// 		spotlight = spotlight->next;
// 	}
// }

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
		scene->ambient_lightning->brightness * AMBIENT_REFLECTION_CONSTANT;
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
	t_ray			OL;
	t_vec3			OS;
	float			Idiffuse;
	float			Ispecular;

	vec3_substract_into(&OL.vec, &model->spotlight->pos, &model->ray_normal->pos);
	dist_to_spotlight = vec3_normalize(&OL.vec);
	Idiffuse = vec3_dot(&model->ray_normal->vec, &OL.vec);
	*illumination = (t_color){0};
	if (Idiffuse <= 0.0f)
		return ;
	*illumination = (t_color){1.0f, 1.0f, 1.0f};
	OL.pos = model->ray_normal->pos;
	// _collect_objects_shades(scene, dist_to_spotlight, &OL, illumination);
	// if (illumination->r == 0.0f
	// 		&& illumination->g == 0.0f 
	// 		&& illumination->b == 0.0f)
	// 	return ;
	vec3_linear_transform(&OS, 2.0f * Idiffuse, &model->ray_normal->vec);
	vec3_substract(&OS, &OL.vec);
	vec3_normalize(&OS);
	Idiffuse *= DIFFUSE_REFLECTION_CONSTANT;
	Ispecular = fmaxf(0.0f, -vec3_dot(&OS, &model->ray_from_camera->vec));
	Ispecular = powf(Ispecular, PHONG_EXPONENT) * SPECULAR_REFLECTION_CONSTANT;
	color_scale(
		illumination, (Idiffuse + Ispecular) * model->spotlight->brightness);
}

static void	_collect_objects_shades(
				t_scene const *scene,
				float dist_to_spotlight,
				t_ray const *ray_to_spotlight,
				t_color *illumination)
{
	float	distance_to_object;


}

static bool	_is_spotlight_behind_object(
				t_scene const *scene,
				float dist_to_spotlight,
				t_ray const *ray_toward_spotlight)
{
	float	distance_to_object;
	t_ray	ray;

	ray.vec = ray_toward_spotlight->vec;
	// ray.pos = ray_toward_spotlight->pos; // TODO: switch to case-specific function
	vec3_linear_transform(&ray.pos, 0.000001f, &ray_toward_spotlight->vec);
	vec3_add(&ray.pos, &ray_toward_spotlight->pos);
	if (fetch_closest_intersection(
			&ray, scene->objects, &distance_to_object) == NULL)
		return (false);
	printf("prout\n");
	return (dist_to_spotlight >= distance_to_object);
}
