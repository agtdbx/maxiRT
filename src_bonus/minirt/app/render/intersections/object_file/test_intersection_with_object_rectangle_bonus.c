/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_intersection_with_object_rectangle_bon        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auguste <auguste@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 19:02:43 by auguste           #+#    #+#             */
/*   Updated: 2024/03/18 19:46:34 by auguste          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt/app/app_bonus.h"

#include <stdbool.h>
#include <math.h>

#include "minirt/app/utils/geometry/geometry_bonus.h"

static bool	is_same_sign(
				float a,
				float b);
static bool	intersect_rectangle(
			t_ray const *ray,
			t_object_rectangle const *rectangle,
			t_intersect_info *intersect_info,
			float denom);

/**
 * Test ray-object_rectangle intersection.
 *
 * @param[in] ray Normalized ray
 * @param[in] rectangle The object_rectangle to intersect
 * @param[out] distance From ray origin to intersection point
 * @returns Wether ray intersects with object_rectangle
 */
bool	test_intersection_with_object_rectangle(
			t_ray const *ray,
			t_object_rectangle const *rectangle,
			t_intersect_info *intersect_info)
{
	float	denom;

	denom = vec3_dot(&ray->vec, &rectangle->normal);
	if (denom < 0.000001f)
		return (intersect_rectangle(ray, rectangle, intersect_info, denom));
	return (false);
}


/**
 * Test ray-object_rectangle intersection, but with an reverse normal.
 *
 * @param[in] ray Normalized ray
 * @param[in] rectangle The object_rectangle to intersect
 * @param[out] distance From ray origin to intersection point
 * @returns Wether ray intersects with object_rectangle
 */
bool	test_intersection_with_object_rectangle_reverse(
			t_ray const *ray,
			t_object_rectangle const *rectangle,
			t_intersect_info *intersect_info)
{
	float	denom;

	denom = vec3_dot(&ray->vec, &rectangle->normal);
	if (denom > -0.000001f)
		return (intersect_rectangle(ray, rectangle, intersect_info, denom));
	return (false);
}


static bool	intersect_rectangle(
			t_ray const *ray,
			t_object_rectangle const *rectangle,
			t_intersect_info *intersect_info,
			float denom)
{
	t_vec3	vec;
	t_vec3	q; // Intersect point with plan
	t_vec3	p1_q;
	t_vec3	p2_q;
	t_vec3	p3_q;
	t_vec3	p4_q;
	t_vec3	p1_q_x_p2_q;
	t_vec3	p2_q_x_p3_q;
	t_vec3	p3_q_x_p4_q;
	t_vec3	p4_q_x_p1_q;
	float	o1;
	float	o2;
	float	o3;
	float	o4;

	{
		vec3_substract_into(&vec, &rectangle->point1, &ray->pos);
		intersect_info->sub_part_id = 0;
		intersect_info->distance = vec3_dot(&vec, &rectangle->normal) / denom;
		if (intersect_info->distance < 0.0f)
			return (false);
		// You touch the plan of the rectangle
		// Get intersection point
		q = ray->pos;
		vec3_linear_transform(&q, intersect_info->distance, &ray->vec);

		// Check q is in rectangle
		vec3_substract_into(&p1_q, &rectangle->point1, &q);
		vec3_substract_into(&p2_q, &rectangle->point2, &q);
		vec3_cross(&p1_q, &p2_q, &p1_q_x_p2_q);
		o1 = vec3_dot(&p1_q_x_p2_q, &rectangle->normal);
		if (o1 == 0.0f)
			return (false);

		vec3_substract_into(&p3_q, &rectangle->point3, &q);
		vec3_cross(&p2_q, &p3_q, &p2_q_x_p3_q);
		o2 = vec3_dot(&p2_q_x_p3_q, &rectangle->normal);
		if (o2 == 0.0f || !is_same_sign(o1, o2))
			return (false);

		vec3_substract_into(&p4_q, &rectangle->point4, &q);
		vec3_cross(&p3_q, &p4_q, &p3_q_x_p4_q);
		o3 = vec3_dot(&p3_q_x_p4_q, &rectangle->normal);
		if (o3 == 0.0f || !is_same_sign(o2, o3))
			return (false);

		vec3_cross(&p4_q, &p1_q, &p4_q_x_p1_q);
		o4 = vec3_dot(&p4_q_x_p1_q, &rectangle->normal);
		if (o4 == 0.0f || !is_same_sign(o3, o4))
			return (false);

		return (true);
	}
	return (false);
}


static bool	is_same_sign(
				float a,
				float b)
{
	if (a < 0.0f && b < 0.0f)
		return (true);
	if (a > 0.0f && b > 0.0f)
		return (true);
	return (false);
}

