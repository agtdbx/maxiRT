/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_intersection_with_object_file_bonus.c         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auguste <auguste@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 16:25:15 by tdubois           #+#    #+#             */
/*   Updated: 2024/03/18 19:43:11 by auguste          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt/app/app_bonus.h"

#include <stdbool.h>
#include <math.h>

#include "minirt/app/utils/geometry/geometry_bonus.h"

/**
 * Test ray-object_file intersection.
 *
 * @param[in] ray Normalized ray
 * @param[in] objf The object_file to intersect
 * @param[out] distance From ray origin to intersection point
 * @returns Wether ray intersects with object_file
 */
bool	test_intersection_with_object_file(
			t_ray const *ray,
			t_object_file const *objf,
			t_intersect_info *intersect_info)
{
	t_intersect_info	intersect_test;
	t_intersect_info	local_polygon_test;
	int	i;

	if (test_intersection_with_cube(ray, &objf->bounding_box, &intersect_test))
	{
		i = 0;
		intersect_test.distance = -1.0f;
		intersect_test.sub_part_id = 0;
		while (i < objf->nb_polygons)
		{
			local_polygon_test.distance = -1.0f;
			local_polygon_test.sub_part_id = 0;
			if (objf->polygons[i].type == OBJF_TRIANGLE &&
				test_intersection_with_object_triangle(
					ray, &objf->polygons[i].value.as_objf_triangle,
					&local_polygon_test))
			{
				if (intersect_test.distance > local_polygon_test.distance
					|| intersect_test.distance == -1.0f )
				{
					intersect_test.distance = local_polygon_test.distance;
					intersect_test.sub_part_id = i;
				}
			}
			else if (objf->polygons[i].type == OBJF_RECTANGLE &&
				test_intersection_with_object_rectangle(
					ray, &objf->polygons[i].value.as_objf_rectangle,
					&local_polygon_test))
			{
				if (intersect_test.distance > local_polygon_test.distance
					|| intersect_test.distance == -1.0f )
				{
					intersect_test.distance = local_polygon_test.distance;
					intersect_test.sub_part_id = i;
				}
			}
			i++;
		}
		if (intersect_test.distance != -1.0f)
		{
			intersect_info->distance = intersect_test.distance;
			intersect_info->sub_part_id = intersect_test.sub_part_id;
			return (true);
		}
	}
	return (false);
}
