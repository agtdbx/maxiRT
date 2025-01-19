/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compute_refracted_color.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auguste <auguste@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 16:56:52 by tdubois           #+#    #+#             */
/*   Updated: 2024/03/17 15:23:33 by auguste          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt/app/app.h"

#include <math.h>

#include "minirt/app/utils/geometry/geometry.h"

static bool		get_refracted_ray(
					float ni_over_nt,
					t_ray const *ray,
					t_ray const *normal,
					t_ray *refracted_ray);

static bool		do_intern_intersection(
					t_object const *object,
					t_ray const *refracted_ray,
					t_intersect_info *intersect_info);

static void		intern_reflect(
					t_ray *refracted_ray,
					t_ray const *inside_normal);

static bool		calculate_outside_ray(
					t_object const *object,
					t_ray *refraction_ray,
					t_ray *inside_normal,
					t_ray *outside_ray);

/**
 * Calculate and return the color of the pixel touch when
 * the first object touch is transparent
 *
 * @param[in] scene
 * @param[in] ray
 * @param[in] normal
 * @param[out] color
 */
t_color	compute_refracted_color(
			t_object const *object,
			t_scene const *scene,
			t_ray const *ray,
			t_ray const *normal,
			bool force_transparency)
{
	t_pixel_info		pixel_info;
	t_color				color;
	t_color				base_color;
	t_color				illumination;
	t_ray				refracted_ray;
	t_ray				inside_normal;
	t_ray				outside_ray;
	t_intersect_info	intersect_info;
	float				density;
	float				inv_opacity;

	if (object->opacity == 1.0f && !force_transparency)
		return ((t_color){0});

	if (object->type == OBJ_PLANE || object->type == OBJ_TRIANGLE
			|| object->type == OBJ_PARABOLOID)
		return (intersect_loop_without_param_obj(object, scene, ray));

	density = object->density;
	if (force_transparency)
		density = 1.0f;

	if (!get_refracted_ray(1.0f / density, ray, normal, &refracted_ray))
		return (reflection_outside_object(object, scene, ray, normal));

	refracted_ray.pos = normal->pos;
	if (do_intern_intersection(
			object, &refracted_ray, &intersect_info) == false)
		return ((t_color){0});

	compute_normal_ray(object, &refracted_ray, &intersect_info, &inside_normal);
	vec3_scale(&inside_normal.vec, -1.0f);
	if (force_transparency)
	{
		pixel_info.normal = inside_normal;
		pixel_info.pos = get_object_pixel_pos(object, &refracted_ray,
												&pixel_info.normal, &intersect_info);
		base_color = get_base_color_object(object, &pixel_info.pos);

		if (base_color.a != -1.0f)
		{
			illumination = compute_illumination(scene, object, &refracted_ray,
													&pixel_info.normal);
			base_color.r *= (illumination.r / 255.0f);
			base_color.g *= (illumination.g / 255.0f);
			base_color.b *= (illumination.b / 255.0f);

			if (object->opacity == 1.0f)
				return (base_color);
		}
	}

	if (get_refracted_ray(density, &refracted_ray, &inside_normal,
			&outside_ray) == false && calculate_outside_ray(
			object, &refracted_ray, &inside_normal, &outside_ray) == false)
		return ((t_color){0});
	outside_ray.pos = inside_normal.pos;
	vec3_normalize(&outside_ray.vec);
	outside_ray.depth = ray->depth + 1;
	color = intersect_loop_without_param_obj(object, scene, &outside_ray);

	if (!force_transparency || base_color.a == -1.0f)
		return (color);

	inv_opacity = 1.0f - object->opacity;
	color.r = color.r * inv_opacity + base_color.r * object->opacity;
	color.g = color.g * inv_opacity + base_color.g * object->opacity;
	color.b = color.b * inv_opacity + base_color.b * object->opacity;

	return (color);
}

/**
 * Calculate the refracted ray cause by the difference beetween the
 * air density and the object density
 *
 * @param[in] ni_over_nt
 * @param[in] ray
 * @param[in] normal
 * @param[out] refracted_ray
 * @returns Wether ray is refracted inside the object or not.
 */
static bool	get_refracted_ray(
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

static bool	do_intern_intersection(
				t_object const *object,
				t_ray const *refracted_ray,
				t_intersect_info *intersect_info)
{
	if (object->type == OBJ_SPHERE)
	{
		return (test_intersection_with_sphere_from_inside(
				refracted_ray, &object->value.as_sphere, intersect_info));
	}
	else if (object->type == OBJ_CYLINDER)
	{
		return (test_intersection_with_cylinder_from_inside(
				refracted_ray, &object->value.as_cylinder, intersect_info));
	}
	else if (object->type == OBJ_CONE)
	{
		return (test_intersection_with_cone_from_inside(
				refracted_ray, &object->value.as_cone, intersect_info));
	}
	else if (object->type == OBJ_CUBE)
	{
		return (test_intersection_with_cube_from_inside(
				refracted_ray, &object->value.as_cube, intersect_info));
	}
	else if (object->type == OBJ_OBJECT_FILE)
	{
		return (test_intersection_with_object_file_from_inside(
				refracted_ray, &object->value.as_object_file, intersect_info));
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

static bool	calculate_outside_ray(
				t_object const *object,
				t_ray *refracted_ray,
				t_ray *inside_normal,
				t_ray *outside_ray)
{
	float const			density_factor = object->density;
	int					loop_limit;
	t_intersect_info	intersect_info;

	loop_limit = 10;
	while (loop_limit > 0)
	{
		intern_reflect(refracted_ray, inside_normal);
		if (do_intern_intersection(
				object, refracted_ray, &intersect_info) == false)
			return (false);
		compute_normal_ray(
			object, refracted_ray, &intersect_info, inside_normal);
		vec3_scale(&inside_normal->vec, -1.0f);
		if (get_refracted_ray(
				density_factor, refracted_ray, inside_normal, outside_ray))
			return (true);
		loop_limit--;
	}
	return (false);
}
