/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compute_object_bounding_box_bonus.c                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auguste <auguste@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 22:51:50 by auguste           #+#    #+#             */
/*   Updated: 2024/04/20 18:47:37 by auguste          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt/app/scene/scene_bonus.h"

#include "minirt/app/utils/geometry/geometry_bonus.h"

#include "minirt/app/utils/space_partition/space_partition.h"

#define MIN_SIZE_BBOX 0.1f

static void	calculate_bounding_box_bounds(
				t_object_file *objf,
				float	bounds_x[2],
				float	bounds_y[2],
				float	bounds_z[2]);
static void	set_min_max(
				float const *nb,
				float bounds[2]);
static void	compute_objf_binary_tree(
				t_object_file *objf,
				float	bounds_x[2],
				float	bounds_y[2],
				float	bounds_z[2]);
static void	fill_objf_bbox_tree(
				t_object_binary_part *part,
				char axe,
				int nb_polygons_parent);
static bool	is_bbox_too_small(
				t_bounding_box *bbox);


void	compute_objf_bounding_boxes(
				t_object_file *objf)
{
	float	bounds_x[2];
	float	bounds_y[2];
	float	bounds_z[2];

	// Get mins and max
	calculate_bounding_box_bounds(objf, bounds_x, bounds_y, bounds_z);

	// Calcultate bounding boxes in binary tree
	compute_objf_binary_tree(objf, bounds_x, bounds_y, bounds_z);
}

static void	calculate_bounding_box_bounds(
				t_object_file *objf,
				float	bounds_x[2],
				float	bounds_y[2],
				float	bounds_z[2])
{
	int	i;

	bounds_x[0] = objf->real_vertices[0].x;
	bounds_y[0] = objf->real_vertices[0].x;
	bounds_z[0] = objf->real_vertices[0].y;
	bounds_x[1] = objf->real_vertices[0].y;
	bounds_y[1] = objf->real_vertices[0].z;
	bounds_z[1] = objf->real_vertices[0].z;
	i = 1;
	while (i < objf->nb_vertices)
	{
		set_min_max(&objf->real_vertices[i].x, bounds_x);
		set_min_max(&objf->real_vertices[i].y, bounds_y);
		set_min_max(&objf->real_vertices[i].z, bounds_z);
		i++;
	}
}

static void	set_min_max(
				float const *nb,
				float bounds[2])
{
	if (bounds[0] > *nb)
		bounds[0] = *nb;
	if (bounds[1] < *nb)
		bounds[1] = *nb;
}

static void	compute_objf_binary_tree(
				t_object_file *objf,
				float	bounds_x[2],
				float	bounds_y[2],
				float	bounds_z[2])
{
	int		i;
	char	axe;

	if (objf->binary_partition != NULL)
	{
		free_object_binary_tree(objf->binary_partition);
		objf->binary_partition = NULL;
	}
	create_new_object_binary_tree_part(&objf->binary_partition, objf->nb_polygons);
	if (objf->binary_partition == NULL)
		return ;

	objf->binary_partition->bounding_box.min_x = bounds_x[0];
	objf->binary_partition->bounding_box.min_y = bounds_y[0];
	objf->binary_partition->bounding_box.min_z = bounds_z[0];
	objf->binary_partition->bounding_box.max_x = bounds_x[1];
	objf->binary_partition->bounding_box.max_y = bounds_y[1];
	objf->binary_partition->bounding_box.max_z = bounds_z[1];

	compute_bounding_box_constants(&objf->binary_partition->bounding_box);

	i = 0;
	while (i < objf->nb_polygons)
	{
		add_object_binary_polygons(
			objf->binary_partition->polygons,
			&objf->polygons[i], i, objf->nb_polygons);
		i++;
	}

	axe = 'x';
	if (objf->binary_partition->polygons != NULL
		&& objf->nb_polygons > 0
		&& ! is_bbox_too_small(&objf->binary_partition->bounding_box))
	{
		fill_objf_bbox_tree(objf->binary_partition, axe, objf->nb_polygons);
	}
}


static void	fill_objf_bbox_tree(
				t_object_binary_part *part,
				char axe,
				int nb_polygons_parent)
{
	int						i;
	int						nb_polygons_child1;
	int						nb_polygons_child2;
	float					mid_axe;
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
	if (axe == 'x')
	{
		// Calculate mid axe
		mid_axe = part->bounding_box.max_x - part->bounding_box.min_x;
		mid_axe /= 2.0f;
		mid_axe += part->bounding_box.min_x;

		// Assign mins and max to childs
		child_1->bounding_box.min_x = mid_axe;
		child_2->bounding_box.min_x = part->bounding_box.min_x;
		child_1->bounding_box.max_x = part->bounding_box.max_x;
		child_2->bounding_box.max_x = mid_axe;

		child_1->bounding_box.min_y = part->bounding_box.min_y;
		child_2->bounding_box.min_y = part->bounding_box.min_y;
		child_1->bounding_box.max_y = part->bounding_box.max_y;
		child_2->bounding_box.max_y = part->bounding_box.max_y;

		child_1->bounding_box.min_z = part->bounding_box.min_z;
		child_2->bounding_box.min_z = part->bounding_box.min_z;
		child_1->bounding_box.max_z = part->bounding_box.max_z;
		child_2->bounding_box.max_z = part->bounding_box.max_z;

		axe = 'y';
	}
	else if (axe == 'y')
	{
		// Calculate mid axe
		mid_axe = part->bounding_box.max_y - part->bounding_box.min_y;
		mid_axe /= 2.0f;
		mid_axe += part->bounding_box.min_y;

		// Assign mins and max to childs
		child_1->bounding_box.min_x = part->bounding_box.min_x;
		child_2->bounding_box.min_x = part->bounding_box.min_x;
		child_1->bounding_box.max_x = part->bounding_box.max_x;
		child_2->bounding_box.max_x = part->bounding_box.max_x;

		child_1->bounding_box.min_y = mid_axe;
		child_2->bounding_box.min_y = part->bounding_box.min_y;
		child_1->bounding_box.max_y = part->bounding_box.max_y;
		child_2->bounding_box.max_y = mid_axe;

		child_1->bounding_box.min_z = part->bounding_box.min_z;
		child_2->bounding_box.min_z = part->bounding_box.min_z;
		child_1->bounding_box.max_z = part->bounding_box.max_z;
		child_2->bounding_box.max_z = part->bounding_box.max_z;

		axe = 'z';
	}
	else
	{
		// Calculate mid axe
		mid_axe = part->bounding_box.max_z - part->bounding_box.min_z;
		mid_axe /= 2.0f;
		mid_axe += part->bounding_box.min_z;

		// Assign mins and max to childs
		child_1->bounding_box.min_x = part->bounding_box.min_x;
		child_2->bounding_box.min_x = part->bounding_box.min_x;
		child_1->bounding_box.max_x = part->bounding_box.max_x;
		child_2->bounding_box.max_x = part->bounding_box.max_x;

		child_1->bounding_box.min_y = part->bounding_box.min_y;
		child_2->bounding_box.min_y = part->bounding_box.min_y;
		child_1->bounding_box.max_y = part->bounding_box.max_y;
		child_2->bounding_box.max_y = part->bounding_box.max_y;

		child_1->bounding_box.min_z = mid_axe;
		child_2->bounding_box.min_z = part->bounding_box.min_z;
		child_1->bounding_box.max_z = part->bounding_box.max_z;
		child_2->bounding_box.max_z = mid_axe;

		axe = 'x';
	}

	// Compute bbox constants for childs
	compute_bounding_box_constants(&child_1->bounding_box);
	compute_bounding_box_constants(&child_2->bounding_box);

	i = 0;
	nb_polygons_child1 = 0;
	nb_polygons_child2 = 0;

	// Iterate thought each polygon of main tree part
	while (i < nb_polygons_parent)
	{
		if (is_polygon_inside_bounding_box(
				&child_1->bounding_box, part->polygons[i].polygon))
		{
			add_object_binary_polygons(
				child_1->polygons, part->polygons[i].polygon,
				part->polygons[i].polygon_id, nb_polygons_parent);
			nb_polygons_child1++;
		}

		if (is_polygon_inside_bounding_box(
				&child_2->bounding_box, part->polygons[i].polygon))
		{
			add_object_binary_polygons(
				child_2->polygons, part->polygons[i].polygon,
				part->polygons[i].polygon_id, nb_polygons_parent);
			nb_polygons_child2++;
		}

		i++;
	}

	// Free the useless polygons chain list (now polygons are in childs)
	free_object_binary_polygons(part->polygons);
	part->polygons = NULL;

	part->child_1 = child_1;
	part->child_2 = child_2;

	fill_objf_bbox_tree(child_1, axe, nb_polygons_child1);
	fill_objf_bbox_tree(child_2, axe, nb_polygons_child2);
}


static bool	is_bbox_too_small(
				t_bounding_box *bbox)
{
	return ((bbox->max_x - bbox->min_x) < MIN_SIZE_BBOX
		|| (bbox->max_y - bbox->min_y) < MIN_SIZE_BBOX
		|| (bbox->max_z - bbox->min_z) < MIN_SIZE_BBOX);
}
