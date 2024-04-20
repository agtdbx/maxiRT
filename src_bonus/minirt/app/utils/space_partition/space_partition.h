/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   space_partition.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auguste <auguste@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 14:54:25 by auguste           #+#    #+#             */
/*   Updated: 2024/04/20 17:02:58 by auguste          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SPACE_PARTITION_H
# define SPACE_PARTITION_H

# include "minirt/app/scene/scene_bonus.h"

bool	is_polygon_inside_bounding_box(
			const t_bounding_box *bbox,
			const t_object_polygon *polygon);

bool	is_bbox_in_bbox(
			const t_bounding_box *bbox_out,
			const t_bounding_box *bbox_in);

#endif
