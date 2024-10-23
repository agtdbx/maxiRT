/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compute_bounding_box_constants.c             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gugus <gugus@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 15:40:43 by auguste           #+#    #+#             */
/*   Updated: 2024/06/16 14:30:15 by gugus            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt/app/scene/scene.h"

static void	_calculate_points(
				t_bounding_box *bbox,
				t_vec3 points[8]);
static void _calculate_inv_size(
				t_bounding_box *bbox,
				float *inv_width,
				float *inv_height,
				float *inv_depth);
static void	_set_face_variable(
				t_bouding_box_face *bbox_face,
				t_vec3 const *normal,
				float inv_width,
				float inv_height,
				t_vec3 const *point_ru,
				t_vec3 const *point_lu,
				t_vec3 const *point_rd,
				t_vec3 const *point_ld);


void	compute_bounding_box_constants(
			t_bounding_box *bbox)
{
	float	inv_width;
	float	inv_height;
	float	inv_depth;
	// ruf luf rdf ldf rub lub rdb ldb
	t_vec3	points[8];
	t_vec3	normal;

	// Calculate inv_size
	_calculate_inv_size(bbox, &inv_width, &inv_height, &inv_depth);

	// Calculate points
	_calculate_points(bbox, points);

	// right face
	normal = (t_vec3){1.0f, 0.0f, 0.0f};
	_set_face_variable(
		&bbox->right, &normal, inv_depth, inv_height,
		&points[4], &points[0], &points[6], &points[2]);

	// left face
	normal = (t_vec3){-1.0f, 0.0f, 0.0f};
	_set_face_variable(
		&bbox->left, &normal, inv_depth, inv_height,
		&points[5], &points[1], &points[7], &points[3]);

	// up face
	normal = (t_vec3){0.0f, 1.0f, 0.0f};
	_set_face_variable(
		&bbox->up, &normal, inv_width, inv_depth,
		&points[4], &points[5], &points[0], &points[1]);

	// down face
	normal = (t_vec3){0.0f, -1.0f, 0.0f};
	_set_face_variable(
		&bbox->down, &normal, inv_width, inv_depth,
		&points[6], &points[7], &points[2], &points[3]);

	// front face
	normal = (t_vec3){0.0f, 0.0f, 1.0f};
	_set_face_variable(
		&bbox->front, &normal, inv_width, inv_height,
		&points[0], &points[1], &points[2], &points[3]);

	// back face
	normal = (t_vec3){0.0f, 0.0f, -1.0f};
	_set_face_variable(
		&bbox->back, &normal, inv_width, inv_height,
		&points[4], &points[5], &points[6], &points[7]);
}


static void	_calculate_points(
				t_bounding_box *bbox,
				t_vec3 points[8])
{
	bbox->center.x = bbox->min_x + bbox->half_width;
	bbox->center.y = bbox->min_y + bbox->half_height;
	bbox->center.z = bbox->min_z + bbox->half_depth;

	points[0] = (t_vec3){bbox->max_x, bbox->max_y, bbox->max_z};
	points[1] = (t_vec3){bbox->min_x, bbox->max_y, bbox->max_z};
	points[2] = (t_vec3){bbox->max_x, bbox->min_y, bbox->max_z};
	points[3] = (t_vec3){bbox->min_x, bbox->min_y, bbox->max_z};
	points[4] = (t_vec3){bbox->max_x, bbox->max_y, bbox->min_z};
	points[5] = (t_vec3){bbox->min_x, bbox->max_y, bbox->min_z};
	points[6] = (t_vec3){bbox->max_x, bbox->min_y, bbox->min_z};
	points[7] = (t_vec3){bbox->min_x, bbox->min_y, bbox->min_z};
}


static void _calculate_inv_size(
				t_bounding_box *bbox,
				float *inv_width,
				float *inv_height,
				float *inv_depth)
{
	*inv_width = bbox->max_x - bbox->min_x;
	bbox->half_width = (*inv_width) / 2.0f;
	if (*inv_width != 0.0f)
		*inv_width = 1.0f / (*inv_width);

	*inv_height = bbox->max_y - bbox->min_y;
	bbox->half_height = (*inv_height) / 2.0f;
	if (*inv_height != 0.0f)
		*inv_height = 1.0f / (*inv_height);

	*inv_depth = bbox->max_z - bbox->min_z;
	bbox->half_depth = (*inv_depth) / 2.0f;
	if (*inv_depth != 0.0f)
		*inv_depth = 1.0f / (*inv_depth);
}


static void	_set_face_variable(
				t_bouding_box_face *bbox_face,
				t_vec3 const *normal,
				float inv_width,
				float inv_height,
				t_vec3 const *point_ru,
				t_vec3 const *point_lu,
				t_vec3 const *point_rd,
				t_vec3 const *point_ld)
{
	bbox_face->normal = *normal;
	bbox_face->inv_width = inv_width;
	bbox_face->inv_height = inv_height;
	bbox_face->point_ru = *point_ru;
	bbox_face->point_lu = *point_lu;
	bbox_face->point_rd = *point_rd;
	bbox_face->point_ld = *point_ld;
}
