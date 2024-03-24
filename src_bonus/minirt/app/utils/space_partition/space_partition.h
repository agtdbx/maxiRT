/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   space_partition.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auguste <auguste@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 14:54:25 by auguste           #+#    #+#             */
/*   Updated: 2024/03/24 12:56:55 by auguste          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SPACE_PARTITION_H
# define SPACE_PARTITION_H

# include "minirt/app/scene/scene_bonus.h"

bool	is_polygon_inside_bounding_box(
			t_bounding_box *bbox,
			t_object_polygon *polygon);

bool	is_triangle_collide_cube(
			t_vec3 const *p1,
			t_vec3 const *p2,
			t_vec3 const *p3,
			t_vec3 const *normal,
			t_bounding_box const *bbox);

#endif
