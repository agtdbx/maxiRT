/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_ray_on_sphere.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdubois <tdubois@student.42angouleme.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 10:06:32 by tdubois           #+#    #+#             */
/*   Updated: 2023/06/01 17:51:02 by tdubois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt/app/app.h>

#include <minirt/scene/scene.h>
#include <minirt/utils/geometry.h>

static void	_compute_normal_ray(
				t_sphere const *sphere,
				t_ray const *ray,
				float distance,
				t_ray *normal);

int32_t	render_ray_on_sphere(
		t_scene const *scene,
		t_sphere const *sphere,
		t_ray const *ray,
		float distance)
{
	t_ray	normal;
	float	intensity;

	(void) scene;
	_compute_normal_ray(sphere, ray, distance, &normal);
	intensity = -vec3_dot(&normal.vec, &ray->vec);
	return (255
		| ((int32_t)(sphere->color.r * intensity) << 24)
		| ((int32_t)(sphere->color.g * intensity) << 16)
		| ((int32_t)(sphere->color.b * intensity) << 8));
}

static void	_compute_normal_ray(
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

////////////////////////////////////////////////////////////////////////////////

#define AMBIENT_REFLECTION_CONSTANT 0.1
#define DIFFUSE_REFLECTION_CONSTANT 0.1
#define SPECULAR_REFLECTION_CONSTANT 0.1

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

	illumination->r = scene->ambient_lightning->color.r * AMBIENT_REFLECTION_CONSTANT;
	illumination->g = scene->ambient_lightning->color.g * AMBIENT_REFLECTION_CONSTANT;
	illumination->b = scene->ambient_lightning->color.b * AMBIENT_REFLECTION_CONSTANT;
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
	dist_to_spotlight = vec3_norm(&OL.vec);
	vec3_scale(&OL.vec, 1.0f / dist_to_spotlight);
	Idiffuse = vec3_dot(&normal->vec, &OL.vec);
	OL.pos = normal->pos;
	if (Idiffuse <= 0.0f || _is_spotlight_behind_object(
				scene, dist_to_spotlight, &OL))
		return (0.0f);
	vec3_linear_transform(&OS, 2.0f * Idiffuse, &normal->vec);
	vec3_substract(&OS, &OL.vec);
	Ispecular = -vec3_dot(&OS, &ray->vec);
	Idiffuse *= DIFFUSE_REFLECTION_CONSTANT;
	Ispecular *= SPECULAR_REFLECTION_CONSTANT;
	return (Idiffuse + Ispecular);
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
