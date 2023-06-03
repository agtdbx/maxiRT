/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compute_illumination.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdubois <tdubois@student.42angouleme.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 02:23:39 by tdubois           #+#    #+#             */
/*   Updated: 2023/06/03 01:00:01 by tdubois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt/app/app.h>

#include <minirt/utils/geometry.h>
#include <math.h>

#define AMBIENT_REFLECTION_CONSTANT 0.3f
#define DIFFUSE_REFLECTION_CONSTANT 0.3f
#define SPECULAR_REFLECTION_CONSTANT 0.3f
#define PHONG_EXPONENT 50.0f

static float	_compute_illumination_from_spotlight(
					t_scene const *scene,
					t_ray const *ray,
					t_ray const *normal,
					t_light const *spotlight);
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
void	compute_illumination(
			t_scene const *scene,
			t_ray const *ray,
			t_ray const *normal,
			t_color *illumination)
{
	t_light const	*spotlight;
	float			illumination_from_spotlight;
	float			Iambient;

	Iambient = AMBIENT_REFLECTION_CONSTANT;
	illumination->r = scene->ambient_lightning->color.r * Iambient;
	illumination->g = scene->ambient_lightning->color.g * Iambient;
	illumination->b = scene->ambient_lightning->color.b * Iambient;
	spotlight = scene->spotlights;
	while (spotlight != NULL)
	{
		illumination_from_spotlight = _compute_illumination_from_spotlight(
				scene, ray, normal, spotlight);
		if (illumination_from_spotlight > 0.0f)
		{
			illumination->r += spotlight->color.r * illumination_from_spotlight;
			illumination->g += spotlight->color.g * illumination_from_spotlight;
			illumination->b += spotlight->color.b * illumination_from_spotlight;
		}
		spotlight = spotlight->next;
	}
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
static float	_compute_illumination_from_spotlight(
					t_scene const *scene,
					t_ray const *ray,
					t_ray const *normal,
					t_light const *spotlight)
{
	float			dist_to_spotlight;
	t_ray			OL;
	t_vec3			OS;
	float			Idiffuse;
	float			Ispecular;

	vec3_substract_into(&OL.vec, &spotlight->pos, &normal->pos);
	dist_to_spotlight = vec3_normalize(&OL.vec);
	Idiffuse = vec3_dot(&normal->vec, &OL.vec);
	if (Idiffuse < 0.0f)
		return (0.0f);
	OL.pos = normal->pos;
	if (_is_spotlight_behind_object(scene, dist_to_spotlight, &OL))
		return (0.0f);
	vec3_linear_transform(&OS, 2.0f * Idiffuse, &normal->vec);
	vec3_substract(&OS, &OL.vec);
	vec3_normalize(&OS);
	Idiffuse *= DIFFUSE_REFLECTION_CONSTANT;
	Ispecular = -vec3_dot(&OS, &ray->vec);
	if (Ispecular <= 0.0f)
		return ((Idiffuse) * spotlight->brightness);
	Ispecular = powf(Ispecular, PHONG_EXPONENT) * SPECULAR_REFLECTION_CONSTANT;
	return ((Idiffuse + Ispecular) * spotlight->brightness);
}

static bool	_is_spotlight_behind_object(
				t_scene const *scene,
				float dist_to_spotlight,
				t_ray const *ray_toward_spotlight)
{
	float	distance_to_object;

	if (fetch_closest_intersection(
			ray_toward_spotlight, scene->objects, &distance_to_object) == NULL)
		return (false);
	return (dist_to_spotlight >= distance_to_object);
}
