/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_intersection_with_object_file_bonus.c         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auguste <auguste@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 16:25:15 by tdubois           #+#    #+#             */
/*   Updated: 2024/04/20 18:43:59 by auguste          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt/app/app_bonus.h"

#include <stdbool.h>
#include <math.h>

#include "minirt/app/utils/geometry/geometry_bonus.h"

static bool	intersect_with_binary_part(
				t_ray const *ray,
				t_object_binary_part const *part,
				t_intersect_info *intersect_info);

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

	intersect_info->distance = -1.0f;
	if (objf->binary_partition != NULL)
		return (intersect_with_binary_part(
					ray, objf->binary_partition, intersect_info));
	return (false);
}

static bool	intersect_with_binary_part(
				t_ray const *ray,
				t_object_binary_part const *part,
				t_intersect_info *intersect_info)
{
	int					i;
	bool				collid1;
	bool				collid2;
	t_intersect_info	child1;
	t_intersect_info	child2;
	t_intersect_info	intersect_test;
	t_intersect_info	local_polygon_test;

	// If ray collid with bounding box
	if (part != NULL
		&& test_intersection_with_bounding_box(ray, &part->bounding_box))
	{
		if (part->child_1 != NULL || part->child_2 != NULL)
		{
			child1.distance = -1.0f;
			child2.distance = -1.0f;
			collid1 = intersect_with_binary_part(ray, part->child_1, &child1);
			collid2 = intersect_with_binary_part(ray, part->child_2, &child2);

			if (!collid1 && !collid2)
				return (false);
			if (collid1 && !collid2)
			{
				intersect_info->distance = child1.distance;
				intersect_info->sub_part_id = child1.sub_part_id;
				return (true);
			}
			if (!collid1 && collid2)
			{
				intersect_info->distance = child2.distance;
				intersect_info->sub_part_id = child2.sub_part_id;
				return (true);
			}
			if (child1.distance < child2.distance)
			{
				intersect_info->distance = child1.distance;
				intersect_info->sub_part_id = child1.sub_part_id;
				return (true);
			}
			intersect_info->distance = child2.distance;
			intersect_info->sub_part_id = child2.sub_part_id;
			return (true);
		}
		// If there is polygons, stop recursion and test intersection
		// with all polygons
		else if (part->polygons != NULL)
		{
			intersect_test.distance = -1.0f;
			i = 0;

			while (part->polygons[i].polygon_id != -1)
			{
				local_polygon_test.distance = -1.0f;
				if (part->polygons[i].polygon->type == OBJF_TRIANGLE)
				{
					if (test_intersection_with_object_triangle(
							ray, &part->polygons[i].polygon->value.as_objf_triangle,
							&local_polygon_test))
					{
						if (intersect_test.distance <= 0.0f
							|| local_polygon_test.distance < intersect_test.distance)
						{
							intersect_test.distance = local_polygon_test.distance;
							intersect_test.sub_part_id = part->polygons[i].polygon_id;
						}
					}
				}
				else if (part->polygons[i].polygon->type == OBJF_RECTANGLE)
				{
					if (test_intersection_with_object_rectangle(
							ray, &part->polygons[i].polygon->value.as_objf_rectangle,
							&local_polygon_test))
					{
						if (intersect_test.distance <= 0.0f
							|| local_polygon_test.distance < intersect_test.distance)
						{
							intersect_test.distance = local_polygon_test.distance;
							intersect_test.sub_part_id = part->polygons[i].polygon_id;
						}
					}
				}
				i++;
			}

			if (intersect_test.distance > 0.0f)
			{
				if (intersect_info->distance <= 0.0f
					|| intersect_test.distance < intersect_info->distance)
				{
					intersect_info->distance = intersect_test.distance;
					intersect_info->sub_part_id = intersect_test.sub_part_id;
				}
				return (true);
			}

			return (false);
		}
	}
	return (false);
}
