/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fetch_closest_intersection_in_tree_bonus.c         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gugus <gugus@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 14:48:07 by gugus             #+#    #+#             */
/*   Updated: 2024/10/22 14:05:47 by gugus            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt/app/app_bonus.h"

#include <stddef.h>
#include <stdbool.h>

#include "minirt/app/scene/scene_bonus.h"

static t_object	*_fetch_closest_plane_intersection(
					t_ray const *ray,
					t_object **planes,
					t_intersect_info *intersect_planes);
static t_object	*_fetch_closest_intersection_in_tree(
					t_ray const *ray,
					t_scene_binary_part *tree,
					t_intersect_info *intersect_info);
static t_object *_return_intersection_with_child(
					t_ray const *ray,
					t_scene_binary_part *tree,
					t_intersect_info *intersect_info);
static void		_compute_childs_collisions(
					t_ray const *ray,
					t_scene_binary_part *tree,
					t_object **collid1,
					t_object **collid2,
					t_intersect_info *intersect_child1,
					t_intersect_info *intersect_child2);
static t_object *_return_closest_object_in_childs(
					t_object *collid1,
					t_object *collid2,
					t_intersect_info *intersect_info,
					t_intersect_info *intersect_child1,
					t_intersect_info *intersect_child2);
static t_object *_return_closest_object_in_part(
					t_ray const *ray,
					t_scene_binary_part *tree,
					t_intersect_info *intersect_info);
static t_object	*_return_closest_object(
					t_object *closest_plane,
					t_object *closest_object,
					t_intersect_info *intersect_info,
					t_intersect_info *intersect_planes,
					t_intersect_info *intersect_object);

/**
 * Fetch closest object intersected with scene tree by ray
 * @param[in] ray
 * @param[in] objects
 * @param[out] intersect_info Info of intersect point.
 * @returns A pointer to the closest object, or NULL if no collision.
 * or NULL if ray did not intercept any object.
 */
t_object	*fetch_closest_intersection_in_tree(
				t_ray const *ray,
				t_scene const *scene,
				t_intersect_info *intersect_info)
{
	t_object			*closest_plane;
	t_object			*closest_object;
	t_intersect_info	intersect_planes;
	t_intersect_info	intersect_object;

	closest_plane = NULL;
	intersect_planes.distance = -1;
	intersect_planes.sub_part_id = 0;

	// Get closest plane
	closest_plane = _fetch_closest_plane_intersection(
						ray, scene->planes, &intersect_planes);

	// Get closest object other than plan
	closest_object = NULL;
	if (scene->binary_tree
		&& test_intersection_with_bounding_box(
			ray, &scene->binary_tree->bounding_box))
	{
		closest_object = _fetch_closest_intersection_in_tree(
							ray, scene->binary_tree, &intersect_object);
	}

	// Choose and return closest object
	return (_return_closest_object(
					closest_plane, closest_object,
					intersect_info, &intersect_planes, &intersect_object));
}


static t_object	*_fetch_closest_plane_intersection(
					t_ray const *ray,
					t_object **planes,
					t_intersect_info *intersect_planes)
{
	int					i;
	t_object			*closest_plane;
	t_intersect_info	test;

	i = 0;
	closest_plane = NULL;
	while (planes && planes[i])
	{
		if (test_intersection_with_obj(ray, planes[i], &test)
			&& (intersect_planes->distance == -1 ||
				test.distance < intersect_planes->distance))
		{
			intersect_planes->distance = test.distance;
			intersect_planes->sub_part_id = test.sub_part_id;
			closest_plane = planes[i];
		}
		i++;
	}
	return (closest_plane);
}


static t_object	*_fetch_closest_intersection_in_tree(
					t_ray const *ray,
					t_scene_binary_part *tree,
					t_intersect_info *intersect_info)
{
	t_object			*collid1;
	t_object			*collid2;
	t_intersect_info	intersect_child1;
	t_intersect_info	intersect_child2;

	if (tree->child_1 != NULL || tree->child_2 != NULL)
	{
		// Test only child 2 is not child 1
		if (tree->child_1 == NULL)
			return (_return_intersection_with_child(
						ray, tree->child_2, intersect_info));
		// Test only child 1 is not child 2
		else if (tree->child_2 == NULL)
			return (_return_intersection_with_child(
						ray, tree->child_1, intersect_info));

		// Test only child 2 is not collid bbox child 1
		if (!test_intersection_with_bounding_box_dist(
				ray, &tree->child_1->bounding_box, &intersect_child1))
			return (_fetch_closest_intersection_in_tree(
						ray, tree->child_2, intersect_info));

		// Test only child 1 is not collid bbox child 2
		else if (!test_intersection_with_bounding_box_dist(
				ray, &tree->child_2->bounding_box, &intersect_child2))
			return (_fetch_closest_intersection_in_tree(
						ray, tree->child_1, intersect_info));

		// Get intersection in child
		_compute_childs_collisions(
			ray, tree, &collid1, &collid2,
			&intersect_child1, &intersect_child2);

		// Choose and return closet intersection
		return (_return_closest_object_in_childs(
					collid1, collid2, intersect_info,
					&intersect_child1, &intersect_child2));
	}

	return (_return_closest_object_in_part(
				ray, tree, intersect_info));
}


static t_object *_return_intersection_with_child(
					t_ray const *ray,
					t_scene_binary_part *tree,
					t_intersect_info *intersect_info)
{
	if (!test_intersection_with_bounding_box(
			ray, &tree->bounding_box))
		return (NULL);
	return (_fetch_closest_intersection_in_tree(
				ray, tree, intersect_info));
}


static void	_compute_childs_collisions(
				t_ray const *ray,
				t_scene_binary_part *tree,
				t_object **collid1,
				t_object **collid2,
				t_intersect_info *intersect_child1,
				t_intersect_info *intersect_child2)
{
	*collid1 = NULL;
	*collid2 = NULL;
	if (intersect_child1->distance < intersect_child2->distance)
	{
		*collid1 = _fetch_closest_intersection_in_tree(
					ray, tree->child_1, intersect_child1);
		if (*collid1 == NULL)
			*collid2 = _fetch_closest_intersection_in_tree(
						ray, tree->child_2, intersect_child2);
	}
	else if (intersect_child1->distance > intersect_child2->distance)
	{
		*collid2 = _fetch_closest_intersection_in_tree(
					ray, tree->child_2, intersect_child2);
		if (*collid2 == NULL)
			*collid1 = _fetch_closest_intersection_in_tree(
						ray, tree->child_1, intersect_child1);
	}
	*collid1 = _fetch_closest_intersection_in_tree(
					ray, tree->child_1, intersect_child1);
	*collid2 = _fetch_closest_intersection_in_tree(
					ray, tree->child_2, intersect_child2);
}


static t_object *_return_closest_object_in_childs(
					t_object *collid1,
					t_object *collid2,
					t_intersect_info *intersect_info,
					t_intersect_info *intersect_child1,
					t_intersect_info *intersect_child2)
{
	if (collid1 == NULL && collid2 == NULL)
		return (NULL);
	if (collid1 == NULL)
	{
		intersect_info->distance = intersect_child2->distance;
		intersect_info->sub_part_id = intersect_child2->sub_part_id;
		return (collid2);
	}
	if (collid2 == NULL)
	{
		intersect_info->distance = intersect_child1->distance;
		intersect_info->sub_part_id = intersect_child1->sub_part_id;
		return (collid1);
	}
	if (intersect_child1->distance < intersect_child2->distance)
	{
		intersect_info->distance = intersect_child1->distance;
		intersect_info->sub_part_id = intersect_child1->sub_part_id;
		return (collid1);
	}
	intersect_info->distance = intersect_child2->distance;
	intersect_info->sub_part_id = intersect_child2->sub_part_id;
	return (collid2);
}


static t_object *_return_closest_object_in_part(
					t_ray const *ray,
					t_scene_binary_part *tree,
					t_intersect_info *intersect_info)
{
	int					i;
	t_object			*closest_object;
	t_intersect_info	intersection_object;


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


static t_object	*_return_closest_object(
					t_object *closest_plane,
					t_object *closest_object,
					t_intersect_info *intersect_info,
					t_intersect_info *intersect_planes,
					t_intersect_info *intersect_object)
{
	if (closest_plane == NULL && closest_object == NULL)
		return (NULL);

	else if (closest_plane == NULL)
	{
		intersect_info->distance = intersect_object->distance;
		intersect_info->sub_part_id = intersect_object->sub_part_id;
		return (closest_object);
	}

	else if (closest_object == NULL)
	{
		intersect_info->distance = intersect_planes->distance;
		intersect_info->sub_part_id = intersect_planes->sub_part_id;
		return (closest_plane);
	}

	else if (intersect_object->distance < intersect_planes->distance)
	{
		intersect_info->distance = intersect_object->distance;
		intersect_info->sub_part_id = intersect_object->sub_part_id;
		return (closest_object);
	}

	else
	{
		intersect_info->distance = intersect_planes->distance;
		intersect_info->sub_part_id = intersect_planes->sub_part_id;
		return (closest_plane);
	}
}
