/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_intersection_with_object_triangle_bonu        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auguste <auguste@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 19:02:43 by auguste           #+#    #+#             */
/*   Updated: 2024/03/18 19:46:41 by auguste          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt/app/app.h"

#include <stdbool.h>
#include <math.h>

#include "minirt/app/utils/geometry/geometry.h"

static bool	intersect_triangle(
			t_ray const *ray,
			t_object_triangle const *triangle,
			t_intersect_info *intersect_info);

/**
 * Test ray-object_triangle intersection.
 *
 * @param[in] ray Normalized ray
 * @param[in] triangle The object_triangle to intersect
 * @param[out] distance From ray origin to intersection point
 * @returns Wether ray intersects with object_triangle
 */
bool	test_intersection_with_object_triangle(
			t_ray const *ray,
			t_object_triangle const *triangle,
			t_intersect_info *intersect_info)
{
	if (vec3_dot(&ray->vec, &triangle->normal) > 0.0f)
		return (false);
	return (intersect_triangle(ray, triangle, intersect_info));
}


/**
 * Test ray-object_triangle intersection, but with an reverse normal.
 *
 * @param[in] ray Normalized ray
 * @param[in] triangle The object_triangle to intersect
 * @param[out] distance From ray origin to intersection point
 * @returns Wether ray intersects with object_triangle
 */
bool	test_intersection_with_object_triangle_reverse(
			t_ray const *ray,
			t_object_triangle const *triangle,
			t_intersect_info *intersect_info)
{
	if (vec3_dot(&ray->vec, &triangle->normal) < 0.0f)
		return (false);
	return (intersect_triangle(ray, triangle, intersect_info));
}


static bool	intersect_triangle(
			t_ray const *ray,
			t_object_triangle const *triangle,
			t_intersect_info *intersect_info)
{
	t_vec3	ray_cross_e2;
	t_vec3	s;
	t_vec3	s_cross_e1;
	float	det;
	float	inv_det;
	float	u;
	float	v;

	vec3_cross(&ray->vec, &triangle->edge2, &ray_cross_e2);
	det = vec3_dot(&triangle->edge1, &ray_cross_e2);

	if (det > -0.000001f && det < 0.000001f)
		return (false); // The ray is parallel to triangle

	inv_det = 1.0f / det;
	vec3_substract_into(&s, &ray->pos, &triangle->point1);
	u = inv_det * vec3_dot(&s, &ray_cross_e2);

	if (u < 0 || u > 1)
		return (false);

	vec3_cross(&s, &triangle->edge1, &s_cross_e1);
	v = inv_det * vec3_dot(&ray->vec, &s_cross_e1);

	if (v < 0 || u + v > 1)
		return (false);

	// Now we now that we hit the triange, so go get the distance
	intersect_info->distance = inv_det * vec3_dot(&triangle->edge2, &s_cross_e1);

	if (intersect_info->distance < 0.000001f)
		return (false);

	intersect_info->sub_part_id = 0;
	return (true);
}
