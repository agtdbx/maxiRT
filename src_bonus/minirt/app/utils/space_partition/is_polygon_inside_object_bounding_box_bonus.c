/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_polygon_inside_object_bounding_box_bonus        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auguste <auguste@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 14:49:50 by auguste           #+#    #+#             */
/*   Updated: 2024/04/20 17:02:44 by auguste          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt/app/scene/scene_bonus.h"

#include "minirt/app/utils/space_partition/space_partition.h"

bool	is_polygon_inside_bounding_box(
			const t_bounding_box *bbox,
			const t_object_polygon *polygon)
{
	return (is_bbox_in_bbox(bbox, &polygon->bounding_box));
}
