/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_intersection_with_object_file.c         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gugus <gugus@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 16:25:15 by tdubois           #+#    #+#             */
/*   Updated: 2024/06/16 18:14:57 by gugus            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt/app/app.h"

#include <stdbool.h>
#include <math.h>

#include "minirt/app/utils/geometry/geometry.h"

static bool	_intersect_with_binary_part(
				t_ray const *ray,
				t_object_binary_part const *part,
				t_intersect_info *intersect_info);
static bool _return_intersection_with_child(
				t_ray const *ray,
				t_object_binary_part const *part,
				t_intersect_info *intersect_info);
static void	_compute_childs_intersection(
				t_ray const *ray,
				t_object_binary_part const *part,
				bool *collid1,
				bool *collid2,
				t_intersect_info *child1,
				t_intersect_info *child2);
static bool	_return_closest_intersection(
				bool collid1,
				bool collid2,
				t_intersect_info *intersect_info,
				t_intersect_info *child1,
				t_intersect_info *child2);
static bool	_return_closest_objf_polygon(
				t_ray const *ray,
				t_object_binary_part const *part,
				t_intersect_info *intersect_info);
static void	_get_clostest_objf_polygons(
				t_ray const *ray,
				t_object_binary_part const *part,
				t_intersect_info *intersect_test);

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
	if (objf->binary_partition != NULL
		&& test_intersection_with_bounding_box(
			ray, &objf->binary_partition->bounding_box))
		return (_intersect_with_binary_part(
					ray, objf->binary_partition, intersect_info));
	return (false);
}

static bool	_intersect_with_binary_part(
				t_ray const *ray,
				t_object_binary_part const *part,
				t_intersect_info *intersect_info)
{
	bool				collid1;
	bool				collid2;
	t_intersect_info	child1;
	t_intersect_info	child2;

	// If ray collid with bounding box
	if (part == NULL)
		return (false);

	// If there is at least 1 child, go into it
	if (part->child_1 != NULL || part->child_2 != NULL)
	{
		// If there is no child 1, intersect child 2
		if (part->child_1 == NULL)
			return (_return_intersection_with_child(
						ray, part->child_2, intersect_info));

		// If there is no child 2, intersect child 1
		else if (part->child_2 == NULL)
			return (_return_intersection_with_child(
						ray, part->child_1, intersect_info));

		// If missing child 1 bbox, only check child 2
		if (!test_intersection_with_bounding_box_dist(
				ray, &part->child_1->bounding_box, &child1))
			return (_intersect_with_binary_part(ray, part->child_2, intersect_info));

		// If missing child 2 bbox, only check child 1
		else if (!test_intersection_with_bounding_box_dist(
				ray, &part->child_2->bounding_box, &child2))
			return (_intersect_with_binary_part(ray, part->child_1, intersect_info));

		// Ray collid both childs bbox
		_compute_childs_intersection(
			ray, part, &collid1, &collid2, &child1, &child2);

		return (_return_closest_intersection(
					collid1, collid2, intersect_info, &child1, &child2));
	}

	// If there is polygons, stop recursion and test intersection
	// with all polygons
	return (_return_closest_objf_polygon(
				ray, part, intersect_info));
}


static bool _return_intersection_with_child(
				t_ray const *ray,
				t_object_binary_part const *part,
				t_intersect_info *intersect_info)
{
	if (!test_intersection_with_bounding_box(
			ray, &part->bounding_box))
		return (false);
	return (_intersect_with_binary_part(ray, part, intersect_info));
}


static void	_compute_childs_intersection(
				t_ray const *ray,
				t_object_binary_part const *part,
				bool *collid1,
				bool *collid2,
				t_intersect_info *child1,
				t_intersect_info *child2)
{
	float				distance1;
	float				distance2;

	*collid1 = false;
	*collid2 = false;
	distance1 = child1->distance;
	distance2 = child2->distance;
	child1->distance = -1.0f;
	child2->distance = -1.0f;

	// If bbox child 1 is closer than bbox child 2
	if (distance1 < distance2)
	{
		// Compute fisrt child 1 intersection
		*collid1 = _intersect_with_binary_part(ray, part->child_1, child1);
		// If missing intersction, test for child 2
		if (!(*collid1))
			*collid2 = _intersect_with_binary_part(ray, part->child_2, child2);
	}

	// If bbox child 2 is closer than bbox child 1
	else if (distance1 > distance2)
	{
		// Compute fisrt child 2 intersection
		*collid2 = _intersect_with_binary_part(ray, part->child_2, child2);
		// If missing intersction, test for child 1
		if (!(*collid2))
			*collid1 = _intersect_with_binary_part(ray, part->child_1, child1);
	}

	// Child bbox are at same distance, just compute both intersection
	else
	{
		*collid1 = _intersect_with_binary_part(ray, part->child_1, child1);
		*collid2 = _intersect_with_binary_part(ray, part->child_2, child2);
	}
}


static bool	_return_closest_intersection(
				bool collid1,
				bool collid2,
				t_intersect_info *intersect_info,
				t_intersect_info *child1,
				t_intersect_info *child2)
{
	// If there is no intersection
	if (!collid1 && !collid2)
		return (false);

	// If there is intersection only child 1
	if (collid1 && !collid2)
	{
		intersect_info->distance = child1->distance;
		intersect_info->sub_part_id = child1->sub_part_id;
	}
	// If there is intersection only child 2
	else if (!collid1 && collid2)
	{
		intersect_info->distance = child2->distance;
		intersect_info->sub_part_id = child2->sub_part_id;
	}
	// If there is closer intersection in child 1
	else if (child1->distance < child2->distance)
	{
		intersect_info->distance = child1->distance;
		intersect_info->sub_part_id = child1->sub_part_id;
	}
	// If there is closer intersection in child 2
	else
	{
		intersect_info->distance = child2->distance;
		intersect_info->sub_part_id = child2->sub_part_id;
	}

	return (true);
}


static bool	_return_closest_objf_polygon(
				t_ray const *ray,
				t_object_binary_part const *part,
				t_intersect_info *intersect_info)
{
	t_intersect_info	intersect_test;

	if (part->polygons == NULL)
		return (false);

	intersect_test.distance = -1.0;
	intersect_test.sub_part_id = 0;
	_get_clostest_objf_polygons(ray, part, &intersect_test);

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


static void	_get_clostest_objf_polygons(
				t_ray const *ray,
				t_object_binary_part const *part,
				t_intersect_info *intersect_test)
{
	int					i;
	t_intersect_info	local_polygon_test;

	i = 0;
	intersect_test->distance = -1.0f;
	while (part->polygons[i].polygon_id != -1)
	{
		local_polygon_test.distance = -1.0f;
		if (part->polygons[i].polygon->type == OBJF_TRIANGLE)
		{
			if (test_intersection_with_object_triangle(
					ray, &part->polygons[i].polygon->value.as_objf_triangle,
					&local_polygon_test))
			{
				if (intersect_test->distance <= 0.0f
					|| local_polygon_test.distance < intersect_test->distance)
				{
					intersect_test->distance = local_polygon_test.distance;
					intersect_test->sub_part_id = part->polygons[i].polygon_id;
				}
			}
		}
		else if (part->polygons[i].polygon->type == OBJF_RECTANGLE)
		{
			if (test_intersection_with_object_rectangle(
					ray, &part->polygons[i].polygon->value.as_objf_rectangle,
					&local_polygon_test))
			{
				if (intersect_test->distance <= 0.0f
					|| local_polygon_test.distance < intersect_test->distance)
				{
					intersect_test->distance = local_polygon_test.distance;
					intersect_test->sub_part_id = part->polygons[i].polygon_id;
				}
			}
		}
		i++;
	}
}
