/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   space_partition.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auguste <auguste@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 14:54:25 by auguste           #+#    #+#             */
/*   Updated: 2024/03/23 15:21:53 by auguste          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SPACE_PARTITION_H
# define SPACE_PARTITION_H

# include "minirt/app/scene/scene_bonus.h"

bool	is_polygon_inside_bounding_box(
			t_bounding_box *bbox,
			t_object_polygon *polygon);

int triBoxOverlap(float boxcenter[3],float boxhalfsize[3],float triverts[3][3]);

#endif
