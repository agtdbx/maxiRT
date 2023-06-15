/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compute_refracted_color.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdubois <tdubois@student.42angouleme.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 16:56:52 by tdubois           #+#    #+#             */
/*   Updated: 2023/06/15 17:49:46 by tdubois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt/app/app.h"

/**
 * @param[in] scene
 * @param[in] ray
 * @param[in] normal
 * @param[out] color
 */
// t_color	compute_refracted_color(
// 			t_object const *object,
// 			t_scene const *scene,
// 			t_ray const *ray,
// 			t_ray const *normal)
// {
// 	t_color	refracted_color;
// 	t_ray	refracted_ray;
//
// 	refracted_color = (t_color){ 0 };
// 	if (get_refracted_ray(object, ray, normal, &refracted_ray) == false)
// 	{
// 		//TODO transparency_reflect...
// 		return (refracted_color);
// 	}
// 	// TODO intersect_second(); ...
// 	return (refracted_color);
// }

/**
 * @param[in] ni_over_nt TODO: add description
 * @param[in] ray
 * @param[in] normal
 * @param[out] refracted_ray
 * @returns Wether ray is refracted inside the object or not.
 */
// bool	get_refracted_ray(
// 			float ni_over_nt,
// 			t_ray const *ray,
// 			t_ray const *normal,
// 			t_ray *refracted_ray)
// {
// 	t_vec3	uv;
// 	float	dt;
// 	float	discriminat;
// 	t_vec3	tmp;
//
// 	vec3_dup(&uv, v);
// 	vec3_normalize(&uv);
// 	dt = vec3_dot_product(&uv, n);
// 	discriminat = 1.0f - ni_over_nt * ni_over_nt * (1.0f - dt * dt);
// 	if (discriminat > 0.0f)
// 	{
// 		vec3_dup(refracted, &uv);
// 		vec3_dup(&tmp, n);
// 		vec3_multiply_number(&tmp, dt);
// 		vec3_sub_vec3(refracted, &tmp);
// 		vec3_multiply_number(refracted, ni_over_nt);
// 		vec3_dup(&tmp, n);
// 		vec3_multiply_number(&tmp, sqrt(discriminat));
// 		vec3_sub_vec3(refracted, &tmp);
// 		return (true);
// 	}
// 	return (false);
// }
