/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compute_refracted_color.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouba <aderouba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 16:56:52 by tdubois           #+#    #+#             */
/*   Updated: 2023/06/15 19:04:36 by aderouba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt/app/app.h"

#include <math.h>

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

float	do_intern_intersection(
			t_object const *object,
			t_ray const *refracted_ray);
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
	t_color	refracted_color;
	t_ray	refracted_ray;
	t_ray	inside_normal;
	t_ray	outside_ray;

	float	density_factor;
	float	dst;

	refracted_color = (t_color){ 0 };
	density_factor = 1.0f / object->density;
	if (get_refracted_ray(density_factor, ray, normal, &refracted_ray) == false)
	{
		//TODO transparency_reflect...
		// Normalement c'est bon ca
		return (reflection_outside_object(object, scene, ray, normal));
	}
	// On init le point de depart du rayon refracte
	refracted_ray.pos = refracted_ray.pos;
	// On recupere la distance a laquelle se trouve la sortie de l'objet
	dst = do_intern_intersection(object, &refracted_ray);
	// Si l'intersection fail, on part parce que c'est pas normal
	if (dst < 0.0f)
		return (refracted_color);

	// On calcule la nouvelle normale
	compute_normal_ray(object, &refracted_ray, dst, &inside_normal);
	// On l'inverse pour qu'elle pointe vers le centre de l'objet
	vec3_scale(&inside_normal.vec, -1.0f);

	// techniquement c'est 'object->density / 1.0f' mais bon ^^
	density_factor = object->density;
	if (get_refracted_ray(density_factor, &refracted_ray, &inside_normal, &outside_ray) == false)
	{
		//TODO reflet interne aux objets
		return (refracted_color);
	}
	// On calcule le point de depart du rayon sortant de l'objet
	outside_ray.pos = inside_normal.pos;

	//TODO boucle d'intersection pour determine l'objet de plus proche
	//     autre que l'objet de la refraction, puis renvoyer la couleur
	//     pour la couleurm faut prendre en compte l'illuminations, la texture, les reflets / transparence...

	return (refracted_color);
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
	t_object		*obj;
	t_object		*closest_obj;
	float			dst;
	float			tmp_dst;

	// Set l'origin du point là où y'a l'intersection avec la sphere
	transparency_ray.pos = normal->pos;

	// Calcule de la direction du rayon reflete
	tmp = normal->vec;
	vec3_scale(&tmp,
		2 * vec3_dot(&ray->vec, &normal->vec));
	transparency_ray.vec = ray->vec;
	vec3_substract(&transparency_ray.vec, &tmp);

	// Boucle d'intersection
	dst = -1.0f;
	closest_obj = NULL;
	obj = scene->objects;
	while (obj)
	{
		if (obj != object)
		{
			tmp_dst = -1.0f;
			test_intersection_with_obj(&transparency_ray, obj, &tmp_dst);
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
	return (closest_obj->color);
}


float	do_intern_intersection(
			t_object const *object,
			t_ray const *refracted_ray)
{
	float	dst;

	dst = -1.0f;
	if (object->type == OBJ_SPHERE)
		test_intersection_with_sphere_from_inside(refracted_ray, &object->value.as_sphere, &dst);
	return (dst);
}
