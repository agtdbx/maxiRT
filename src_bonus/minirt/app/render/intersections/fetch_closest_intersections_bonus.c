/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fetch_closest_intersections_bonus.c                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gugus <gugus@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 12:40:24 by tdubois           #+#    #+#             */
/*   Updated: 2024/06/15 22:37:49 by gugus            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt/app/app_bonus.h"

#include <stddef.h>
#include <stdbool.h>

#include "minirt/app/scene/scene_bonus.h"

static t_object	*_fetch_closest_intersection_in_tree(
					t_ray const *ray,
					t_scene_binary_part *tree,
					t_intersect_info *intersect_info);

/**
 * Fetch closest object intersected by ray
 * @param[in] ray
 * @param[in] objects
 * @param[out] distance The distance to the closest object or NULL.
 * @returns A pointer to the closest object
 * or NULL if ray did not intercept any object.
 */
t_object	*fetch_closest_intersection(
				t_ray const *ray,
				t_object *objects,
				t_intersect_info *intersect_info)
{
	t_intersect_info	actual_intersect_info;
	t_object			*intersected_object;

	intersected_object = NULL;
	intersect_info->distance = -1;
	while (objects != NULL)
	{
		if (test_intersection_with_obj(ray, objects, &actual_intersect_info)
			&& !(0 <= intersect_info->distance
				&& intersect_info->distance <= actual_intersect_info.distance))
		{
			intersect_info->distance = actual_intersect_info.distance;
			intersect_info->sub_part_id = actual_intersect_info.sub_part_id;
			intersected_object = objects;
		}
		objects = objects->next;
	}
	return (intersected_object);
}

t_object	*fetch_closest_intersection_in_tree(
				t_ray const *ray,
				t_scene const *scene,
				t_intersect_info *intersect_info)
{
	int					i;
	// t_object 			*actual;
	t_object			*closest_plane;
	t_object			*closest_object;
	t_intersect_info	intersect_planes_test;
	t_intersect_info	intersect_planes;
	t_intersect_info	intersect_object;

	// actual = scene->objects;
	closest_plane = NULL;
	intersect_planes.distance = -1;
	intersect_planes.sub_part_id = 0;

	// Get closest plane
	// while (actual)
	// {
	// 	if (actual->type == OBJ_PLANE)
	// 	{
	// 		if (test_intersection_with_obj(
	// 				ray, actual, &intersect_planes_test)
	// 			&& (intersect_planes.distance == -1 ||
	// 				intersect_planes.distance < intersect_planes_test.distance))
	// 		{
	// 			intersect_planes.distance = intersect_planes_test.distance;
	// 			intersect_planes.sub_part_id = intersect_planes_test.sub_part_id;
	// 			closest_plane = actual;
	// 		}
	// 	}
	// 	actual = actual->next;
	// }
	i = 0;
	while (scene->planes && scene->planes[i])
	{
		if (test_intersection_with_obj(ray, scene->planes[i], &intersect_planes_test)
			&& (intersect_planes.distance == -1 ||
				intersect_planes.distance < intersect_planes_test.distance))
		{
			intersect_planes.distance = intersect_planes_test.distance;
			intersect_planes.sub_part_id = intersect_planes_test.sub_part_id;
			closest_plane = scene->planes[i];
		}
		i++;
	}

	// Get closest object other than plan
	closest_object = _fetch_closest_intersection_in_tree(
						ray, scene->binary_tree, &intersect_object);

	if (closest_plane == NULL && closest_object == NULL)
		return (NULL);

	else if (closest_plane == NULL)
	{
		intersect_info->distance = intersect_object.distance;
		intersect_info->sub_part_id = intersect_object.sub_part_id;
		return (closest_object);
	}

	else if (closest_object == NULL)
	{
		intersect_info->distance = intersect_planes.distance;
		intersect_info->sub_part_id = intersect_planes.sub_part_id;
		return (closest_plane);
	}

	else if (intersect_object.distance < intersect_planes.distance)
	{
		intersect_info->distance = intersect_object.distance;
		intersect_info->sub_part_id = intersect_object.sub_part_id;
		return (closest_object);
	}

	else
	{
		intersect_info->distance = intersect_planes.distance;
		intersect_info->sub_part_id = intersect_planes.sub_part_id;
		return (closest_plane);
	}
}

static t_object	*_fetch_closest_intersection_in_tree(
					t_ray const *ray,
					t_scene_binary_part *tree,
					t_intersect_info *intersect_info)
{
	int					i;
	t_object			*collid1;
	t_object			*collid2;
	t_object			*closest_object;
	t_intersect_info	intersection_child1;
	t_intersect_info	intersection_child2;
	t_intersect_info	intersection_object;

	if (tree == NULL)
		return (NULL);

	if (!test_intersection_with_bounding_box(ray, &tree->bounding_box))
		return (NULL);

	if (tree->child_1 != NULL || tree->child_2 != NULL)
	{
		collid1 = _fetch_closest_intersection_in_tree(
					ray, tree->child_1, &intersection_child1);
		collid2 = _fetch_closest_intersection_in_tree(
					ray, tree->child_2, &intersection_child2);

		if (collid1 == NULL && collid2 == NULL)
			return (NULL);
		if (collid1 == NULL)
		{
			intersect_info->distance = intersection_child2.distance;
			intersect_info->sub_part_id = intersection_child2.sub_part_id;
			return (collid2);
		}
		if (collid2 == NULL)
		{
			intersect_info->distance = intersection_child1.distance;
			intersect_info->sub_part_id = intersection_child1.sub_part_id;
			return (collid1);
		}
		if (intersection_child1.distance < intersection_child2.distance)
		{
			intersect_info->distance = intersection_child1.distance;
			intersect_info->sub_part_id = intersection_child1.sub_part_id;
			return (collid1);
		}
		intersect_info->distance = intersection_child2.distance;
		intersect_info->sub_part_id = intersection_child2.sub_part_id;
		return (collid2);
	}

	if (tree->objects == NULL)
		return (NULL);

	i = 0;
	closest_object = NULL;
	intersect_info->distance = -1.0f;
	while (tree->objects[i] != NULL)
	{
		if (test_intersection_with_obj(
				ray, tree->objects[i], &intersection_object)
			&& (intersect_info->distance == -1.0f
				|| intersection_object.distance < intersect_info->distance))
		{
			intersect_info->distance = intersection_object.distance;
			intersect_info->sub_part_id = intersection_object.sub_part_id;
			closest_object = tree->objects[i];
		}
		i++;
	}
	return (closest_object);
}
