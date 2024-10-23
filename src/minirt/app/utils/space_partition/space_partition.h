/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   space_partition.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gugus <gugus@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 14:54:25 by auguste           #+#    #+#             */
/*   Updated: 2024/06/16 18:29:27 by gugus            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SPACE_PARTITION_H
# define SPACE_PARTITION_H

# include "minirt/app/scene/scene.h"

# define MIN_SIZE_BBOX 0.1f
# define MIN_SIZE_SCENE_BBOX 5.0f

bool	is_bbox_in_bbox(
			const t_bounding_box *bbox_out,
			const t_bounding_box *bbox_in);

bool	is_bbox_too_small(
			t_bounding_box *bbox,
			float limit);

void	compute_childs_bbox(
			t_bounding_box *parent_bbox,
			t_bounding_box *child1_bbox,
			t_bounding_box *child2_bbox);

void	set_min_max(
			float *min,
			float *max,
			float *test);
#endif
