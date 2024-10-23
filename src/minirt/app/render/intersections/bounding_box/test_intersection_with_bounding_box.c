/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_intersection_with_bounding_box.c        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gugus <gugus@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 19:02:43 by auguste           #+#    #+#             */
/*   Updated: 2024/06/16 16:34:20 by gugus            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt/app/app.h"

#include <stdbool.h>
#include <math.h>

#include "minirt/app/utils/geometry/geometry.h"

static void	_test_intersection_with_bouding_box_face(
				t_ray const *ray,
				t_bouding_box_face const *face,
				t_intersect_info *intersect_info,
				bool *collide);
static bool	_is_intersect_bouding_box_face(
				t_ray const *ray,
				t_bouding_box_face const *face,
				t_intersect_info *intersect_info);
static bool	is_same_sign(
				float a,
				float b);

/**
 * Test ray-object_bouding_box_face intersection.
 *
 * @param[in] ray Normalized ray
 * @param[in] bounding_box The bounding_box to intersect
 * @returns Wether ray intersects with object_bounding_box
 */
bool	test_intersection_with_bounding_box(
			t_ray const *ray,
			t_bounding_box const *bbox)
{
	if (bbox->min_x <= ray->pos.x  && ray->pos.x <= bbox->max_x
		&& bbox->min_y <= ray->pos.y && ray->pos.y <= bbox->max_y
		&& bbox->min_z <= ray->pos.z && ray->pos.z <= bbox->max_z)
		return (true);

	return (_is_intersect_bouding_box_face(
			ray, &bbox->front, NULL)
		|| _is_intersect_bouding_box_face(
			ray, &bbox->back, NULL)
		|| _is_intersect_bouding_box_face(
			ray, &bbox->left, NULL)
		|| _is_intersect_bouding_box_face(
			ray, &bbox->right, NULL)
		|| _is_intersect_bouding_box_face(
			ray, &bbox->up, NULL)
		|| _is_intersect_bouding_box_face(
			ray, &bbox->down, NULL));
}

/**
 * Test ray-object_bouding_box_face intersection.
 *
 * @param[in] ray Normalized ray
 * @param[in] bounding_box The bounding_box to intersect
 * @param[out] intersect_info From ray origin to intersection point
 * @returns Wether ray intersects with object_bounding_box
 */
bool	test_intersection_with_bounding_box_dist(
			t_ray const *ray,
			t_bounding_box const *bbox,
			t_intersect_info *intersect_info)
{
	bool				collide;
	t_intersect_info	test;

	collide = false;
	intersect_info->distance = -1;
	intersect_info->sub_part_id = 0;
	test.distance = -1;
	test.sub_part_id = 0;

	_test_intersection_with_bouding_box_face(
		ray, &bbox->front, intersect_info, &collide);
	_test_intersection_with_bouding_box_face(
		ray, &bbox->back, intersect_info, &collide);
	_test_intersection_with_bouding_box_face(
		ray, &bbox->left, intersect_info, &collide);
	_test_intersection_with_bouding_box_face(
		ray, &bbox->right, intersect_info, &collide);
	_test_intersection_with_bouding_box_face(
		ray, &bbox->up, intersect_info, &collide);
	_test_intersection_with_bouding_box_face(
		ray, &bbox->down, intersect_info, &collide);

	return (collide);
}


static void	_test_intersection_with_bouding_box_face(
				t_ray const *ray,
				t_bouding_box_face const *face,
				t_intersect_info *intersect_info,
				bool *collide)
{
	t_intersect_info	test;

	if (_is_intersect_bouding_box_face(
			ray, face, &test))
	{
		*collide = true;
		if (intersect_info->distance == -1
			|| (intersect_info->distance < test.distance))
			intersect_info->distance = test.distance;
	}
}


static bool	_is_intersect_bouding_box_face(
				t_ray const *ray,
				t_bouding_box_face const *face,
				t_intersect_info *intersect_info)
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
		vec3_substract_into(&vec, &face->point_lu, &ray->pos);
		distance = vec3_dot(&vec, &face->normal) / denom;
		if (distance < 0.0f)
			return (false);
		// You touch the plan of the face
		// Get intersection point
		q = ray->pos;
		vec3_linear_transform(&q, distance, &ray->vec);

		// Check q is in face
		vec3_substract_into(&p1_q, &face->point_lu, &q);
		vec3_substract_into(&p2_q, &face->point_ld, &q);
		vec3_cross(&p1_q, &p2_q, &p1_q_x_p2_q);
		o1 = vec3_dot(&p1_q_x_p2_q, &face->normal);
		if (o1 == 0.0f)
			return (false);

		vec3_substract_into(&p3_q, &face->point_rd, &q);
		vec3_cross(&p2_q, &p3_q, &p2_q_x_p3_q);
		o2 = vec3_dot(&p2_q_x_p3_q, &face->normal);
		if (o2 == 0.0f || !is_same_sign(o1, o2))
			return (false);

		vec3_substract_into(&p4_q, &face->point_ru, &q);
		vec3_cross(&p3_q, &p4_q, &p3_q_x_p4_q);
		o3 = vec3_dot(&p3_q_x_p4_q, &face->normal);
		if (o3 == 0.0f || !is_same_sign(o2, o3))
			return (false);

		vec3_cross(&p4_q, &p1_q, &p4_q_x_p1_q);
		o4 = vec3_dot(&p4_q_x_p1_q, &face->normal);
		if (o4 == 0.0f || !is_same_sign(o3, o4))
			return (false);

		// Save distance if there is intersect info
		if (intersect_info != NULL)
		{
			intersect_info->distance = distance;
			intersect_info->sub_part_id = 0;
		}

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

