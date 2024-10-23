/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_bbox_too_small.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gugus <gugus@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 12:05:11 by gugus             #+#    #+#             */
/*   Updated: 2024/06/16 12:07:08 by gugus            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt/app/scene/scene.h"

#include "minirt/app/utils/space_partition/space_partition.h"

bool	is_bbox_too_small(
			t_bounding_box *bbox,
			float limit)
{
	return ((bbox->max_x - bbox->min_x) < limit
		|| (bbox->max_y - bbox->min_y) < limit
		|| (bbox->max_z - bbox->min_z) < limit);
}
