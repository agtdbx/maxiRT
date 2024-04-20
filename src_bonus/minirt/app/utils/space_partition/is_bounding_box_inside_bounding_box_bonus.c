/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_bounding_box_inside_bounding_box_bonus.c        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auguste <auguste@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 16:45:03 by auguste           #+#    #+#             */
/*   Updated: 2024/04/20 16:45:03 by auguste          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt/app/scene/scene_bonus.h"

#include "minirt/app/utils/space_partition/space_partition.h"

bool	is_bbox_in_bbox(
			const t_bounding_box *bbox_out,
			const t_bounding_box *bbox_in)
{
	return (bbox_out->min_x <= bbox_in->max_x
			&& bbox_in->min_x <= bbox_out->max_x
			&& bbox_out->min_y <= bbox_in->max_y
			&& bbox_in->min_y <= bbox_out->max_y
			&& bbox_out->min_z <= bbox_in->max_z
			&& bbox_in->min_z <= bbox_out->max_z);
}
