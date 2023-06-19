/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compute_refracted_color.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouba <aderouba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 16:56:52 by tdubois           #+#    #+#             */
/*   Updated: 2023/06/19 15:39:14 by aderouba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt/app/app.h"

#include <math.h>
#include <stdio.h>

#include "minirt/app/utils/geometry/geometry.h"

bool	get_refracted_ray(
			float ni_over_nt,
			t_ray const *ray,
			t_ray const *normal,
			t_ray *refracted_ray);

t_color	reflection_outside_object(
			t_object const *object,
			t_scene const *scene,
			t_ray const *ray,
			t_ray const *normal);

t_color	intersect_loop_without_param_obj(
			t_object const *object,
			t_scene const *scene,
			t_ray const *ray);

bool	do_intern_intersection(
			t_object const *object,
			t_ray const *refracted_ray,
			float *dst);

bool	calculate_outside_ray(
			t_object const *object,
			t_ray *refraction_ray,
			t_ray *inside_normal,
			t_ray *outside_ray);
/**
 * @param[in] scene
 * @param[in] ray
 * @param[in] normal
 * @param[out] color
 */
t_color	compute_refracted_color(
			t_object const *object,
			t_scene const *scene,
			t_ray const *ray,
			t_ray const *normal)
{
	t_ray	refracted_ray;
	t_ray	inside_normal;
	t_ray	outside_ray;

	float	density_factor;
	float	dst;

	if (object->opacity == 1.0f)
		return ((t_color){ 0 });
	density_factor = 1.0f / object->density;
	if (get_refracted_ray(density_factor, ray, normal, &refracted_ray) == false)
	{
		// transparency_reflect...
		// Normalement c'est bon ca
		return (reflection_outside_object(object, scene, ray, normal));
	}
	// On init le point de depart du rayon refracte
	refracted_ray.pos = normal->pos;

	// On recupere la distance a laquelle se trouve la sortie de l'objet
	if (do_intern_intersection(object, &refracted_ray, &dst) == false)
		return ((t_color){ 0 });

	// On calcule la nouvelle normale
	compute_normal_ray(object, &refracted_ray, dst, &inside_normal);
	// On l'inverse pour qu'elle pointe vers le centre de l'objet
	vec3_scale(&inside_normal.vec, -1.0f);

	// techniquement c'est 'object->density / 1.0f' mais bon ^^
	density_factor = object->density;
	if (get_refracted_ray(density_factor, &refracted_ray, &inside_normal, &outside_ray) == false
		&& calculate_outside_ray(object, &refracted_ray, &inside_normal, &outside_ray) == false)
		return ((t_color){ 0 });
	// On calcule le point de depart du rayon sortant de l'objet
	outside_ray.pos = inside_normal.pos;
	vec3_normalize(&outside_ray.vec);

	return (intersect_loop_without_param_obj(object, scene, &outside_ray));
}

/**
 * @param[in] ni_over_nt TODO: add description
 * @param[in] ray
 * @param[in] normal
 * @param[out] refracted_ray
 * @returns Wether ray is refracted inside the object or not.
 */
bool	get_refracted_ray(
			float ni_over_nt,
			t_ray const *ray,
			t_ray const *normal,
			t_ray *refracted_ray)
{
	t_vec3	uv;
	float	dt;
	float	discriminat;
	t_vec3	tmp;

	uv = ray->vec;
	vec3_normalize(&uv);
	dt = vec3_dot(&uv, &normal->vec);
	discriminat = 1.0f - ni_over_nt * ni_over_nt * (1.0f - dt * dt);
	if (discriminat > 0.0f)
	{
		refracted_ray->vec = uv;
		tmp = normal->vec;
		vec3_scale(&tmp, dt);
		vec3_substract(&refracted_ray->vec, &tmp);
		vec3_scale(&refracted_ray->vec, ni_over_nt);
		tmp = normal->vec;
		vec3_scale(&tmp, sqrt(discriminat));
		vec3_substract(&refracted_ray->vec, &tmp);
		return (true);
	}
	return (false);
}


// Fonction pour faire le reflet exterieur a l'objet
t_color	reflection_outside_object(
			t_object const *object,
			t_scene const *scene,
			t_ray const *ray,
			t_ray const *normal)
{
	t_vec3			tmp;
	t_ray			transparency_ray;

	// Set l'origin du point là où y'a l'intersection avec la sphere
	transparency_ray.pos = normal->pos;

	// Calcule de la direction du rayon reflete
	tmp = normal->vec;
	vec3_scale(&tmp,
		2 * vec3_dot(&ray->vec, &normal->vec));
	transparency_ray.vec = ray->vec;
	vec3_substract(&transparency_ray.vec, &tmp);

	vec3_normalize(&transparency_ray.vec);

	return (intersect_loop_without_param_obj(object, scene, &transparency_ray));
}

t_color	intersect_loop_without_param_obj(
			t_object const *object,
			t_scene const *scene,
			t_ray const *ray)
{
	t_object		*obj;
	t_object		*closest_obj;
	float			dst;
	float			tmp_dst;

	// Boucle d'intersection
	dst = -1.0f;
	closest_obj = NULL;
	obj = scene->objects;
	while (obj)
	{
		if (obj != object)
		{
			tmp_dst = -1.0f;
			test_intersection_with_obj(ray, obj, &tmp_dst);
			if (tmp_dst >= 0.0f && (dst < 0.0f || tmp_dst < dst))
			{
				dst = tmp_dst;
				closest_obj = obj;
			}
		}
		obj = obj->next;
	}

	// Renvois de la couleur
	if (closest_obj == NULL)
		return ((t_color){0});
	// return (render_ray_on_object(scene, closest_obj, ray, dst));

	t_ray	normal;
	t_color	illumination;
	t_color	color = closest_obj->color;

	compute_normal_ray(closest_obj, ray, dst, &normal);
	compute_illumination(scene, ray, &normal, &illumination);

	color.r *= illumination.r / 255.0f;
	color.g *= illumination.g / 255.0f;
	color.b *= illumination.b / 255.0f;
	return (color);
}


bool	do_intern_intersection(
			t_object const *object,
			t_ray const *refracted_ray,
			float *dst)
{
	if (object->type == OBJ_SPHERE)
	{
		return (test_intersection_with_sphere_from_inside(
			refracted_ray, &object->value.as_sphere, dst));
	}
	return (false);
}

static void	intern_reflect(
				t_ray *refracted_ray,
				t_ray const *inside_normal)
{
	t_vec3	tmp;

	refracted_ray->pos = inside_normal->pos;
	tmp = inside_normal->vec;
	vec3_scale(&tmp,
		2 * vec3_dot(&refracted_ray->vec, &inside_normal->vec));
	vec3_substract(&refracted_ray->pos, &tmp);
}

bool	calculate_outside_ray(
			t_object const *object,
			t_ray *refracted_ray,
			t_ray *inside_normal,
			t_ray *outside_ray)
{
	float const	density_factor = object->density;
	int			loop_limit;
	float		dst;

	loop_limit = 10;
	while (loop_limit > 0)
	{
		intern_reflect(refracted_ray, inside_normal);
		if (do_intern_intersection(object, refracted_ray, &dst) == false)
			return (false);
		compute_normal_ray(object, refracted_ray, dst, inside_normal);
		vec3_scale(&inside_normal->vec, -1.0f);
		if (get_refracted_ray(
				density_factor, refracted_ray, inside_normal, outside_ray))
			return (true);
		loop_limit--;
	}
	return (false);
}
