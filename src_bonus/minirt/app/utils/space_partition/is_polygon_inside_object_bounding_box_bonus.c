/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_polygon_inside_object_bounding_box_bonus        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auguste <auguste@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 14:49:50 by auguste           #+#    #+#             */
/*   Updated: 2024/03/24 12:49:20 by auguste          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt/app/scene/scene_bonus.h"

#include "minirt/app/utils/space_partition/space_partition.h"

bool	is_polygon_inside_bounding_box(
			t_bounding_box *bbox,
			t_object_polygon *polygon)
{
	if (polygon->type == OBJF_TRIANGLE)
	{
		return (is_triangle_collide_cube(
					&polygon->value.as_objf_triangle.point1,
					&polygon->value.as_objf_triangle.point2,
					&polygon->value.as_objf_triangle.point3,
					&polygon->value.as_objf_triangle.normal,
					bbox));
	}
	if (polygon->type == OBJF_RECTANGLE)
	{
		return (is_triangle_collide_cube(
					&polygon->value.as_objf_rectangle.point1,
					&polygon->value.as_objf_rectangle.point2,
					&polygon->value.as_objf_rectangle.point3,
					&polygon->value.as_objf_rectangle.normal,
					bbox)
				|| is_triangle_collide_cube(
					&polygon->value.as_objf_rectangle.point1,
					&polygon->value.as_objf_rectangle.point3,
					&polygon->value.as_objf_rectangle.point4,
					&polygon->value.as_objf_rectangle.normal,
					bbox));
	}
	return (false);
}
