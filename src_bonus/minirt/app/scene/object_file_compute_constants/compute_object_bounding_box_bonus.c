/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compute_object_bounding_box_bonus.c                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auguste <auguste@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 22:51:50 by auguste           #+#    #+#             */
/*   Updated: 2024/03/21 19:35:50 by auguste          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt/app/scene/scene_bonus.h"

#include "minirt/app/utils/geometry/geometry_bonus.h"

#define MIN_SIZE_BBOX 1.0f

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
				char axe);
static void	compute_bounding_box_constants(
				t_object_bounding_box *bounding_box);
static bool	is_in_bound(
				float min,
				float max,
				float nb);
static bool is_polygon_inside_object_bounding_box(
				t_object_bounding_box *bbox,
				t_object_polygon *polygon);
static bool	is_point_inside_object_bounding_box(
				t_object_bounding_box *bbox,
				t_vec3 const *point);
static bool	is_bbox_too_small(
				t_object_bounding_box *bbox);

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
	create_new_object_binary_tree_part(&objf->binary_partition);
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
			&objf->binary_partition->polygons,
			&objf->polygons[i], i);
		i++;
	}

	axe = 'x';
	if (objf->binary_partition->polygons != NULL
		&& objf->nb_polygons > 0
		&& ! is_bbox_too_small(&objf->binary_partition->bounding_box))
	{
		fill_objf_bbox_tree(objf->binary_partition, axe);
	}
}


static void	fill_objf_bbox_tree(
				t_object_binary_part *part,
				char axe)
{
	int						child_1_polygons;
	int						child_2_polygons;
	float					mid_axe;
	t_object_binary_part	*child_1;
	t_object_binary_part	*child_2;
	t_object_binary_polygon	*actual;

	if (part->polygons == NULL
		|| is_bbox_too_small(&part->bounding_box))
		return ;

	create_new_object_binary_tree_part(&child_1);
	if (child_1 == NULL)
		return ;
	create_new_object_binary_tree_part(&child_2);
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

	// Iterate thought each polygon of main tree part
	child_1_polygons = 0;
	child_2_polygons = 0;
	actual = part->polygons;

	while (actual)
	{
		if (is_polygon_inside_object_bounding_box(
				&child_1->bounding_box, actual->polygon))
		{
			add_object_binary_polygons(
				&child_1->polygons, actual->polygon, actual->polygon_id);
			child_1_polygons++;
		}

		if (is_polygon_inside_object_bounding_box(
				&child_2->bounding_box, actual->polygon))
		{
			add_object_binary_polygons(
				&child_2->polygons, actual->polygon, actual->polygon_id);
			child_2_polygons++;
		}

		actual = actual->next;
	}

	// Free the useless polygons chain list (now polygons are in childs)
	free_object_binary_polygons(part->polygons);
	part->polygons = NULL;

	part->child_1 = child_1;
	part->child_2 = child_2;

	fill_objf_bbox_tree(child_1, axe);
	fill_objf_bbox_tree(child_2, axe);
}

static void	compute_bounding_box_constants(
				t_object_bounding_box *bbox)
{
	float	inv_width;
	float	inv_height;
	float	inv_depth;
	t_vec3	p_ruf;
	t_vec3	p_luf;
	t_vec3	p_rdf;
	t_vec3	p_ldf;
	t_vec3	p_rub;
	t_vec3	p_lub;
	t_vec3	p_rdb;
	t_vec3	p_ldb;

	// Calculate inv_size
	inv_width = bbox->max_x - bbox->min_x;
	if (inv_width != 0.0f)
		inv_width = 1.0f / inv_width;
	inv_height = bbox->max_y - bbox->min_y;
	if (inv_height != 0.0f)
		inv_height = 1.0f / inv_height;
	inv_depth = bbox->max_z - bbox->min_z;
	if (inv_depth != 0.0f)
		inv_depth = 1.0f / inv_depth;

	// Calculate points
	p_ruf = (t_vec3){bbox->max_x, bbox->max_y, bbox->max_z};
	p_luf = (t_vec3){bbox->min_x, bbox->max_y, bbox->max_z};
	p_rdf = (t_vec3){bbox->max_x, bbox->min_y, bbox->max_z};
	p_ldf = (t_vec3){bbox->min_x, bbox->min_y, bbox->max_z};
	p_rub = (t_vec3){bbox->max_x, bbox->max_y, bbox->min_z};
	p_lub = (t_vec3){bbox->min_x, bbox->max_y, bbox->min_z};
	p_rdb = (t_vec3){bbox->max_x, bbox->min_y, bbox->min_z};
	p_ldb = (t_vec3){bbox->min_x, bbox->min_y, bbox->min_z};

	// right face
	bbox->right.normal = (t_vec3){1.0f, 0.0f, 0.0f};
	bbox->right.inv_width = inv_depth;
	bbox->right.inv_height = inv_height;
	bbox->right.point_ru = p_rub;
	bbox->right.point_lu = p_ruf;
	bbox->right.point_rd = p_rdb;
	bbox->right.point_ld = p_rdf;

	// left faceS
	bbox->left.normal = (t_vec3){-1.0f, 0.0f, 0.0f};
	bbox->left.inv_width = inv_depth;
	bbox->left.inv_height = inv_height;
	bbox->left.point_ru = p_lub;
	bbox->left.point_lu = p_luf;
	bbox->left.point_rd = p_ldb;
	bbox->left.point_ld = p_ldf;

	// up face
	bbox->up.normal = (t_vec3){0.0f, 1.0f, 0.0f};
	bbox->up.inv_width = inv_width;
	bbox->up.inv_height = inv_depth;
	bbox->up.point_ru = p_rub;
	bbox->up.point_lu = p_lub;
	bbox->up.point_rd = p_ruf;
	bbox->up.point_ld = p_luf;

	// down face
	bbox->down.normal = (t_vec3){0.0f, -1.0f, 0.0f};
	bbox->down.inv_width = inv_width;
	bbox->down.inv_height = inv_depth;
	bbox->down.point_ru = p_rdb;
	bbox->down.point_lu = p_ldb;
	bbox->down.point_rd = p_rdf;
	bbox->down.point_ld = p_ldf;

	// front face
	bbox->front.normal = (t_vec3){0.0f, 0.0f, 1.0f};
	bbox->front.inv_width = inv_width;
	bbox->front.inv_height = inv_height;
	bbox->front.point_ru = p_ruf;
	bbox->front.point_lu = p_luf;
	bbox->front.point_rd = p_rdf;
	bbox->front.point_ld = p_ldf;

	// back face
	bbox->back.normal = (t_vec3){0.0f, 0.0f, -1.0f};
	bbox->back.inv_width = inv_width;
	bbox->back.inv_height = inv_height;
	bbox->back.point_ru = p_rub;
	bbox->back.point_lu = p_lub;
	bbox->back.point_rd = p_rdb;
	bbox->back.point_ld = p_ldb;
}

static bool is_polygon_inside_object_bounding_box(
				t_object_bounding_box *bbox,
				t_object_polygon *polygon)
{
	if (polygon->type == OBJF_TRIANGLE)
		return (is_point_inside_object_bounding_box(
					bbox, &polygon->value.as_objf_triangle.point1)
				|| is_point_inside_object_bounding_box(
					bbox, &polygon->value.as_objf_triangle.point2)
				|| is_point_inside_object_bounding_box(
					bbox, &polygon->value.as_objf_triangle.point3));
	if (polygon->type == OBJF_RECTANGLE)
		return (is_point_inside_object_bounding_box(
					bbox, &polygon->value.as_objf_rectangle.point1)
				|| is_point_inside_object_bounding_box(
					bbox, &polygon->value.as_objf_rectangle.point2)
				|| is_point_inside_object_bounding_box(
					bbox, &polygon->value.as_objf_rectangle.point3)
				|| is_point_inside_object_bounding_box(
					bbox, &polygon->value.as_objf_rectangle.point4));
	return (false);
}

static bool	is_point_inside_object_bounding_box(
				t_object_bounding_box *bbox,
				t_vec3 const *point)
{
	if (!is_in_bound(
			bbox->min_x,
			bbox->max_x,
			point->x))
		return (false);
	if (!is_in_bound(
			bbox->min_y,
			bbox->max_y,
			point->y))
		return (false);
	if (!is_in_bound(
			bbox->min_z,
			bbox->max_z,
			point->z))
		return (false);
	return (true);
}


static bool	is_in_bound(
				float min,
				float max,
				float nb)
{
	return (min <= nb && nb <= max);
}


static bool	is_bbox_too_small(
				t_object_bounding_box *bbox)
{
	return ((bbox->max_x - bbox->min_x) < MIN_SIZE_BBOX
		|| (bbox->max_y - bbox->min_y) < MIN_SIZE_BBOX
		|| (bbox->max_z - bbox->min_z) < MIN_SIZE_BBOX);
}
