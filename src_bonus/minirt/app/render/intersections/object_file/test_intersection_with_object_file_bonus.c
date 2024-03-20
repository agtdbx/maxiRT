/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_intersection_with_object_file_bonus.c         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auguste <auguste@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 16:25:15 by tdubois           #+#    #+#             */
/*   Updated: 2024/03/20 23:00:14 by auguste          ###   ########.fr       */
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
	t_intersect_info		intersect_test;
	t_intersect_info		local_polygon_test;
	t_object_binary_polygon	*actual;

	// If ray collid with bounding box
	if (part != NULL
		&& test_intersection_with_object_bounding_box(ray, &part->bounding_box))
	{

		// If there is polygons, stop recursion and test intersection
		// with all polygons
		if (part->polygons != NULL)
		{
			intersect_test.distance = -1.0f;
			actual = part->polygons;

			while (actual != NULL)
			{
				local_polygon_test.distance = -1.0f;
				if (actual->polygon->type == OBJF_TRIANGLE)
				{
					if (test_intersection_with_object_triangle(
							ray, &actual->polygon->value.as_objf_triangle,
							&local_polygon_test))
					{
						if (intersect_test.distance == -1.0f
							|| local_polygon_test.distance < intersect_test.distance)
						{
							intersect_test.distance = local_polygon_test.distance;
							intersect_test.sub_part_id = actual->polygon_id;
						}
					}
				}
				else if (actual->polygon->type == OBJF_RECTANGLE)
				{
					if (test_intersection_with_object_rectangle(
							ray, &actual->polygon->value.as_objf_rectangle,
							&local_polygon_test))
					{
						if (intersect_test.distance == -1.0f
							|| local_polygon_test.distance < intersect_test.distance)
						{
							intersect_test.distance = local_polygon_test.distance;
							intersect_test.sub_part_id = actual->polygon_id;
						}
					}
				}
				actual = actual->next;
			}

			if (intersect_test.distance != -1.0f)
			{
				intersect_info->distance = intersect_test.distance;
				intersect_info->sub_part_id = intersect_test.sub_part_id;
				return (true);
			}

			return (false);
		}
		else
		{
			return (intersect_with_binary_part(
						ray, part->child_1, intersect_info)
					|| intersect_with_binary_part(
						ray, part->child_2, intersect_info));
		}
	}
	return (false);
}

//bool	test_intersection_with_object_file(
//			t_ray const *ray,
//			t_object_file const *objf,
//			t_intersect_info *intersect_info)
//{
//	t_intersect_info	intersect_test;
//	t_intersect_info	local_polygon_test;
//	int	i;

//	if (test_intersection_with_cube(ray, &objf->bounding_box, &intersect_test))
//	{
//		i = 0;
//		intersect_test.distance = -1.0f;
//		intersect_test.sub_part_id = 0;
//		while (i < objf->nb_polygons)
//		{
//			local_polygon_test.distance = -1.0f;
//			local_polygon_test.sub_part_id = 0;
//			if (objf->polygons[i].type == OBJF_TRIANGLE &&
//				test_intersection_with_object_triangle(
//					ray, &objf->polygons[i].value.as_objf_triangle,
//					&local_polygon_test))
//			{
//				if (intersect_test.distance > local_polygon_test.distance
//					|| intersect_test.distance == -1.0f )
//				{
//					intersect_test.distance = local_polygon_test.distance;
//					intersect_test.sub_part_id = i;
//				}
//			}
//			else if (objf->polygons[i].type == OBJF_RECTANGLE &&
//				test_intersection_with_object_rectangle(
//					ray, &objf->polygons[i].value.as_objf_rectangle,
//					&local_polygon_test))
//			{
//				if (intersect_test.distance > local_polygon_test.distance
//					|| intersect_test.distance == -1.0f )
//				{
//					intersect_test.distance = local_polygon_test.distance;
//					intersect_test.sub_part_id = i;
//				}
//			}
//			i++;
//		}
//		if (intersect_test.distance != -1.0f)
//		{
//			intersect_info->distance = intersect_test.distance;
//			intersect_info->sub_part_id = intersect_test.sub_part_id;
//			return (true);
//		}
//	}
//	return (false);
//}
