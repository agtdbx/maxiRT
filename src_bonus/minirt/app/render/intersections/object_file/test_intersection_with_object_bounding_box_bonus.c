/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_intersection_with_object_bounding_box_        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auguste <auguste@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 19:02:43 by auguste           #+#    #+#             */
/*   Updated: 2024/03/18 22:40:08 by auguste          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt/app/app_bonus.h"

#include <stdbool.h>
#include <math.h>

#include "minirt/app/utils/geometry/geometry_bonus.h"

static bool	is_same_sign(
				float a,
				float b);
static bool	test_intersection_with_object_face(
			t_ray const *ray,
			t_object_face const *face);

/**
 * Test ray-object_face intersection.
 *
 * @param[in] ray Normalized ray
 * @param[in] bounding_box The object_bounding_box to intersect
 * @param[out] distance From ray origin to intersection point
 * @returns Wether ray intersects with object_bounding_box
 */
bool	test_intersection_with_object_bounding_box(
			t_ray const *ray,
			t_object_bounding_box const *bounding_box)
{
	return (test_intersection_with_object_face(
			ray, &bounding_box->front)
		|| test_intersection_with_object_face(
			ray, &bounding_box->back)
		|| test_intersection_with_object_face(
			ray, &bounding_box->left)
		|| test_intersection_with_object_face(
			ray, &bounding_box->right)
		|| test_intersection_with_object_face(
			ray, &bounding_box->up)
		|| test_intersection_with_object_face(
			ray, &bounding_box->down));
}


static bool	test_intersection_with_object_face(
			t_ray const *ray,
			t_object_face const *face)
{
	float	denom;
	float	distance;
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

	denom = vec3_dot(&ray->vec, &face->normal);
	if (denom < 0.000001f)
	{
		vec3_substract_into(&vec, &face->point_ul, &ray->pos);
		distance = vec3_dot(&vec, &face->normal) / denom;
		if (distance < 0.0f)
			return (false);
		// You touch the plan of the face
		// Get intersection point
		q = ray->pos;
		vec3_linear_transform(&q, distance, &ray->vec);

		// Check q is in face
		vec3_substract_into(&p1_q, &face->point_ul, &q);
		vec3_substract_into(&p2_q, &face->point_dl, &q);
		vec3_cross(&p1_q, &p2_q, &p1_q_x_p2_q);
		o1 = vec3_dot(&p1_q_x_p2_q, &face->normal);
		if (o1 == 0.0f)
			return (false);

		vec3_substract_into(&p3_q, &face->point_dr, &q);
		vec3_cross(&p2_q, &p3_q, &p2_q_x_p3_q);
		o2 = vec3_dot(&p2_q_x_p3_q, &face->normal);
		if (o2 == 0.0f || !is_same_sign(o1, o2))
			return (false);

		vec3_substract_into(&p4_q, &face->point_ur, &q);
		vec3_cross(&p3_q, &p4_q, &p3_q_x_p4_q);
		o3 = vec3_dot(&p3_q_x_p4_q, &face->normal);
		if (o3 == 0.0f || !is_same_sign(o2, o3))
			return (false);

		vec3_cross(&p4_q, &p1_q, &p4_q_x_p1_q);
		o4 = vec3_dot(&p4_q_x_p1_q, &face->normal);
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

