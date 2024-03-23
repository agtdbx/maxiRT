/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compute_bounding_box_constants_bonus.c             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auguste <auguste@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 15:40:43 by auguste           #+#    #+#             */
/*   Updated: 2024/03/23 18:59:29 by auguste          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt/app/scene/scene_bonus.h"

void	compute_bounding_box_constants(
			t_bounding_box *bbox)
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
	bbox->half_width = inv_width / 2.0f;
	if (inv_width != 0.0f)
		inv_width = 1.0f / inv_width;

	inv_height = bbox->max_y - bbox->min_y;
	bbox->half_height = inv_height / 2.0f;
	if (inv_height != 0.0f)
		inv_height = 1.0f / inv_height;

	inv_depth = bbox->max_z - bbox->min_z;
	bbox->half_depth = inv_depth / 2.0f;
	if (inv_depth != 0.0f)
		inv_depth = 1.0f / inv_depth;

	// Calculate points
	bbox->center.x = bbox->min_x + bbox->half_width;
	bbox->center.y = bbox->min_y + bbox->half_height;
	bbox->center.z = bbox->min_z + bbox->half_depth;

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
