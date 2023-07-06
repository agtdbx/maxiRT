/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_intersection_with_cube.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouba <aderouba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 16:25:15 by tdubois           #+#    #+#             */
/*   Updated: 2023/07/06 18:25:52 by aderouba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt/app/app.h"

#include <stdbool.h>
#include <math.h>

#include "minirt/app/utils/geometry/geometry.h"

/**
 * Test ray-cube intersection
 *
 * @param[in] ray Normalized ray
 * @param[in] cylinder
 * @param[out] distance From ray origin to intersection point
 * @returns Wether ray intersects with plane
 */
bool	test_intersection_with_cube(
			t_ray const *ray,
			t_cube const *cube,
			t_intersect_info *intersect_info)
{
	bool				is_face_intersect;
	t_intersect_info	test;

	test.distance = 0.0f;
	test.sub_part_id = -1;
	is_face_intersect = false;
	is_face_intersect += intersection_with_right(ray, cube, &test);
	is_face_intersect += intersection_with_left(ray, cube, &test);
	is_face_intersect += intersection_with_top(ray, cube, &test);
	is_face_intersect += intersection_with_bot(ray, cube, &test);
	is_face_intersect += intersection_with_front(ray, cube, &test);
	is_face_intersect += intersection_with_back(ray, cube, &test);
	if (is_face_intersect)
	{
		intersect_info->distance = test.distance;
		intersect_info->sub_part_id = test.sub_part_id;
	}
	return (is_face_intersect);
}
