/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compute_object_bounding_box_bonus.c                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auguste <auguste@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 22:51:50 by auguste           #+#    #+#             */
/*   Updated: 2024/04/21 18:34:14 by auguste          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt/app/scene/scene_bonus.h"

#include <stdlib.h>

#include "minirt/app/utils/geometry/geometry_bonus.h"
#include "minirt/app/utils/space_partition/space_partition.h"

#define MIN_SIZE_BBOX 0.1f

static void	calculate_bounding_box_bounds(
				t_object_file *objf,
				t_bounding_box *bbox);
static void	compute_objf_binary_tree(
				t_object_file *objf,
				t_bounding_box *bbox);
static void	fill_objf_bbox_tree(
				t_object_binary_part *part,
				int nb_polygons_parent);
static bool	is_bbox_too_small(
				t_bounding_box *bbox);


void	compute_objf_bounding_boxes(
				t_object_file *objf,
				t_bounding_box *bbox)
{
	// Get mins and max
	calculate_bounding_box_bounds(objf, bbox);

	// Calcultate bounding boxes in binary tree
	compute_objf_binary_tree(objf, bbox);
}

static void	calculate_bounding_box_bounds(
				t_object_file *objf,
				t_bounding_box *bbox)
{
	int	i;

	bbox->min_x = objf->real_vertices[0].x;
	bbox->max_x = objf->real_vertices[0].x;
	bbox->min_y = objf->real_vertices[0].y;
	bbox->max_y = objf->real_vertices[0].y;
	bbox->min_z = objf->real_vertices[0].z;
	bbox->max_z = objf->real_vertices[0].z;
	i = 1;
	while (i < objf->nb_vertices)
	{
		set_min_max(&bbox->min_x, &bbox->max_x, &objf->real_vertices[i].x);
		set_min_max(&bbox->min_y, &bbox->max_y, &objf->real_vertices[i].y);
		set_min_max(&bbox->min_z, &bbox->max_z, &objf->real_vertices[i].z);
		i++;
	}
	compute_bounding_box_constants(bbox);
}

static void	compute_objf_binary_tree(
				t_object_file *objf,
				t_bounding_box *bbox)
{
	int		i;

	if (objf->binary_partition != NULL)
	{
		free_object_binary_tree(objf->binary_partition);
		objf->binary_partition = NULL;
	}
	create_new_object_binary_tree_part(&objf->binary_partition, objf->nb_polygons);
	if (objf->binary_partition == NULL)
		return ;

	objf->binary_partition->bounding_box = *bbox;

	i = 0;
	while (i < objf->nb_polygons)
	{
		add_object_binary_polygons(
			objf->binary_partition->polygons,
			&objf->polygons[i], i, objf->nb_polygons);
		i++;
	}

	if (objf->binary_partition->polygons != NULL
		&& objf->nb_polygons > 0
		&& ! is_bbox_too_small(&objf->binary_partition->bounding_box))
	{
		fill_objf_bbox_tree(objf->binary_partition, objf->nb_polygons);
	}
}


static void	fill_objf_bbox_tree(
				t_object_binary_part *part,
				int nb_polygons_parent)
{
	int						i;
	int						nb_polygons_child1;
	int						nb_polygons_child2;
	t_object_binary_part	*child_1;
	t_object_binary_part	*child_2;

	if (nb_polygons_parent < 2
		|| is_bbox_too_small(&part->bounding_box))
		return ;

	create_new_object_binary_tree_part(&child_1, nb_polygons_parent);
	if (child_1 == NULL)
		return ;
	create_new_object_binary_tree_part(&child_2, nb_polygons_parent);
	if (child_2 == NULL)
	{
		free_object_binary_tree(child_1);
		return ;
	}

	// Cut main bbox in half by axe to childs have bbox
	compute_childs_bbox(
		&part->bounding_box,
		&child_1->bounding_box,
		&child_2->bounding_box);

	// Compute bbox constants for childs
	compute_bounding_box_constants(&child_1->bounding_box);
	compute_bounding_box_constants(&child_2->bounding_box);

	i = 0;
	nb_polygons_child1 = 0;
	nb_polygons_child2 = 0;

	// Iterate thought each polygon of main tree part
	while (i < nb_polygons_parent)
	{
		if (is_bbox_in_bbox(
				&child_1->bounding_box,
				&part->polygons[i].polygon->bounding_box))
		{
			add_object_binary_polygons(
				child_1->polygons, part->polygons[i].polygon,
				part->polygons[i].polygon_id, nb_polygons_parent);
			nb_polygons_child1++;
		}

		if (is_bbox_in_bbox(
				&child_2->bounding_box,
				&part->polygons[i].polygon->bounding_box))
		{
			add_object_binary_polygons(
				child_2->polygons, part->polygons[i].polygon,
				part->polygons[i].polygon_id, nb_polygons_parent);
			nb_polygons_child2++;
		}

		i++;
	}

	// Free the useless polygons chain list (now polygons are in childs)
	free(part->polygons);
	part->polygons = NULL;

	part->child_1 = child_1;
	part->child_2 = child_2;

	fill_objf_bbox_tree(child_1, nb_polygons_child1);
	fill_objf_bbox_tree(child_2, nb_polygons_child2);
}


static bool	is_bbox_too_small(
				t_bounding_box *bbox)
{
	return ((bbox->max_x - bbox->min_x) < MIN_SIZE_BBOX
		|| (bbox->max_y - bbox->min_y) < MIN_SIZE_BBOX
		|| (bbox->max_z - bbox->min_z) < MIN_SIZE_BBOX);
}
