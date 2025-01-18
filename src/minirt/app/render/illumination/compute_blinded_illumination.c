/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compute_blinded_illumination.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gugus <gugus@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 02:23:39 by tdubois           #+#    #+#             */
/*   Updated: 2025/01/18 04:37:53 by gugus            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt/app/app.h"

#include <math.h>
#include <stddef.h>

#include "minirt/app/app_config.h"
#include "minirt/app/utils/geometry/geometry.h"
#include <minirt/app/scene/scene.h>

static void		_collect_blinded_illumination_from_spotlight(
					t_scene const *scene,
					t_ray const *ray,
					t_light *light,
					t_color *ill);
float			_compute_blind_ratio(
					t_ray const *ray,
					t_light *light);
static t_color	_is_light_hidden(
					t_object const *objects,
					float dist_to_spotlight,
					t_ray const *ray);
static void		apply_shadow_to_illumination(
					t_object const *objects,
					t_color *illumination,
					float dist_to_spotlight,
					t_ray const *ray);

t_color	compute_blinded_illumination(
			t_scene const *scene,
			t_ray const *ray)
{
	t_color	ill_from_spotlight;
	t_color	illumination;
	t_light	*light;

	light = scene->spotlights;
	illumination = (t_color){0};
	while (light != NULL)
	{
		ill_from_spotlight = (t_color){0};
		_collect_blinded_illumination_from_spotlight(
			scene, ray, light, &ill_from_spotlight);
		illumination.r += ill_from_spotlight.r * light->color.r;
		illumination.g += ill_from_spotlight.g * light->color.g;
		illumination.b += ill_from_spotlight.b * light->color.b;
		light = light->next;
	}
	return (illumination);
}

static void	_collect_blinded_illumination_from_spotlight(
				t_scene const *scene,
				t_ray const *ray,
				t_light *light,
				t_color *ill)
{
	float			dist_to_spotlight;
	t_vec3			ol;
	float			idiffuse;
	float			blind_ratio;
	float			parallel_ratio;

	vec3_substract_into(&ol, &light->pos, &ray->pos);
	dist_to_spotlight = vec3_normalize(&ol);
	idiffuse = vec3_dot(&ray->vec, &ol);
	if (idiffuse <= 0.0f)
		return ;

	if (light->parallel)
	{
		parallel_ratio = -vec3_dot(&light->dir, &ol);
		if ((parallel_ratio + 1.0f) * 180.0f < light->min_angle)
			return ;
	}

	blind_ratio = _compute_blind_ratio(ray, light);
	if (blind_ratio == 0.0f)
		return ;

	*ill = _is_light_hidden(scene->objects, dist_to_spotlight, ray);
	if (ill->r <= 0.0f && ill->g <= 0.0f && ill->b <= 0.0f && ill->a != -1.0f)
	{
		*ill = (t_color){0};
		return ;
	}
	color_scale(ill, blind_ratio * light->brightness);
}

float	_compute_blind_ratio(
				t_ray const *ray,
				t_light *light)
{
	t_intersect_info	inter_info;
	t_sphere			light_bulb;
	t_vec3				inter_pos;
	t_vec3				inter_vec;
	float				blind_ratio;

	// Collide with light blind influence
	light_bulb.pos = light->pos;
	light_bulb.radius = 1.0f;
	light_bulb.radius2 = light_bulb.radius * light_bulb.radius;
	if (!test_intersection_with_sphere(ray, &light_bulb, &inter_info))
		return (0.0f);

	// Calculate intersection point
	inter_pos = ray->pos;
	vec3_linear_transform(&inter_pos, inter_info.distance, &ray->vec);

	// Calulate blind ratio
	vec3_substract_into(&inter_vec, &light->pos, &inter_pos);
	vec3_normalize(&inter_vec);

	blind_ratio = vec3_dot(&inter_vec, &ray->vec);
	return (powf(blind_ratio, 10.0f));
}

static t_color	_is_light_hidden(
					t_object const *objects,
					float dist_to_spotlight,
					t_ray const *ray)
{
	t_color				illumination;

	illumination = (t_color){1.0f, 1.0f, 1.0f, 1.0f};
	while (objects != NULL)
	{
		apply_shadow_to_illumination(
			objects, &illumination, dist_to_spotlight, ray);
		if (illumination.r <= 0.0f
			&& illumination.g <= 0.0f
			&& illumination.b <= 0.0f
			&& illumination.a != -1.0f)
			return (illumination);
		objects = objects->next;
	}
	return (illumination);
}

static void	apply_shadow_to_illumination(
				t_object const *objects,
				t_color *illumination,
				float dist_to_spotlight,
				t_ray const *ray)
{
	t_intersect_info	distance_to_object;
	t_color				base_color;
	t_ray				normal;
	t_vec2				pixel_pos;

	if (test_intersection_with_obj(
			ray, objects, &distance_to_object)
		&& (distance_to_object.distance < dist_to_spotlight))
	{
		compute_normal_ray(objects, ray,
			&distance_to_object, &normal);
		pixel_pos = get_object_pixel_pos(objects, ray,
				&normal, &distance_to_object);
		base_color = get_base_color_object(objects, &pixel_pos);
		if (base_color.a == -1.0f)
		{
			if (test_intersection_with_obj_from_inside(
					ray, objects, &distance_to_object)
				&& distance_to_object.distance < dist_to_spotlight)
			{
				compute_normal_ray(objects, ray,
					&distance_to_object, &normal);
				vec3_scale(&normal.vec, -1.0f);
				pixel_pos = get_object_pixel_pos(objects, ray,
						&normal, &distance_to_object);
				base_color = get_base_color_object(objects, &pixel_pos);
				if (base_color.a == -1.0f)
				{
					illumination->r = 1.0f;
					illumination->g = 1.0f;
					illumination->b = 1.0f;
					return ;
				}
			}
			else
			{
				illumination->r = 1.0f;
				illumination->g = 1.0f;
				illumination->b = 1.0f;
				return ;
			}
		}
		if (objects->opacity == 1.0f)
		{
			*illumination = (t_color){0};
			return ;
		}
		illumination->r -= powf(objects->opacity,
				1 + base_color.r * g_opacity_color_ratio);
		illumination->g -= powf(objects->opacity,
				1 + base_color.g * g_opacity_color_ratio);
		illumination->b -= powf(objects->opacity,
				1 + base_color.b * g_opacity_color_ratio);
		illumination->a = base_color.a;
	}
}
