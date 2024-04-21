/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compute_childs_bbox_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auguste <auguste@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 13:43:06 by auguste           #+#    #+#             */
/*   Updated: 2024/04/21 18:13:55 by auguste          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt/app/scene/scene_bonus.h"

void	compute_childs_bbox(
			t_bounding_box *parent_bbox,
			t_bounding_box *child1_bbox,
			t_bounding_box *child2_bbox)
{
	const float	x_size = parent_bbox->max_x - parent_bbox->min_x;
	const float	y_size = parent_bbox->max_y - parent_bbox->min_y;
	const float	z_size = parent_bbox->max_z - parent_bbox->min_z;
	float	mid_axe;

	// Cut main bbox in half by axe to childs have bbox
	if (x_size > y_size && x_size > z_size)
	{
		// Calculate mid axe
		mid_axe = x_size / 2.0f;
		mid_axe += parent_bbox->min_x;

		// Assign mins and max to childs
		child1_bbox->min_x = mid_axe;
		child2_bbox->min_x = parent_bbox->min_x;
		child1_bbox->max_x = parent_bbox->max_x;
		child2_bbox->max_x = mid_axe;

		child1_bbox->min_y = parent_bbox->min_y;
		child2_bbox->min_y = parent_bbox->min_y;
		child1_bbox->max_y = parent_bbox->max_y;
		child2_bbox->max_y = parent_bbox->max_y;

		child1_bbox->min_z = parent_bbox->min_z;
		child2_bbox->min_z = parent_bbox->min_z;
		child1_bbox->max_z = parent_bbox->max_z;
		child2_bbox->max_z = parent_bbox->max_z;
	}
	else if (y_size > x_size && y_size > z_size)
	{
		// Calculate mid axe
		mid_axe = y_size / 2.0f;
		mid_axe += parent_bbox->min_y;

		// Assign mins and max to childs
		child1_bbox->min_x = parent_bbox->min_x;
		child2_bbox->min_x = parent_bbox->min_x;
		child1_bbox->max_x = parent_bbox->max_x;
		child2_bbox->max_x = parent_bbox->max_x;

		child1_bbox->min_y = mid_axe;
		child2_bbox->min_y = parent_bbox->min_y;
		child1_bbox->max_y = parent_bbox->max_y;
		child2_bbox->max_y = mid_axe;

		child1_bbox->min_z = parent_bbox->min_z;
		child2_bbox->min_z = parent_bbox->min_z;
		child1_bbox->max_z = parent_bbox->max_z;
		child2_bbox->max_z = parent_bbox->max_z;
	}
	else
	{
		// Calculate mid axe
		mid_axe = z_size / 2.0f;
		mid_axe += parent_bbox->min_z;

		// Assign mins and max to childs
		child1_bbox->min_x = parent_bbox->min_x;
		child2_bbox->min_x = parent_bbox->min_x;
		child1_bbox->max_x = parent_bbox->max_x;
		child2_bbox->max_x = parent_bbox->max_x;

		child1_bbox->min_y = parent_bbox->min_y;
		child2_bbox->min_y = parent_bbox->min_y;
		child1_bbox->max_y = parent_bbox->max_y;
		child2_bbox->max_y = parent_bbox->max_y;

		child1_bbox->min_z = mid_axe;
		child2_bbox->min_z = parent_bbox->min_z;
		child1_bbox->max_z = parent_bbox->max_z;
		child2_bbox->max_z = mid_axe;
	}
}
