/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   space_partition.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auguste <auguste@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 14:54:25 by auguste           #+#    #+#             */
/*   Updated: 2024/04/21 18:14:56 by auguste          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SPACE_PARTITION_H
# define SPACE_PARTITION_H

# include "minirt/app/scene/scene_bonus.h"

bool	is_bbox_in_bbox(
			const t_bounding_box *bbox_out,
			const t_bounding_box *bbox_in);

void	compute_childs_bbox(
			t_bounding_box *parent_bbox,
			t_bounding_box *child1_bbox,
			t_bounding_box *child2_bbox);

void	set_min_max(
			float *min,
			float *max,
			float *test);
#endif
