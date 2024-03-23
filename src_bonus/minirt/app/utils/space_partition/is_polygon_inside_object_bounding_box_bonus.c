/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_polygon_inside_object_bounding_box_bonus        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auguste <auguste@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 14:49:50 by auguste           #+#    #+#             */
/*   Updated: 2024/03/23 18:59:51 by auguste          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt/app/scene/scene_bonus.h"

#include "minirt/app/utils/space_partition/space_partition.h"

static bool is_triangle_inside_object_bounding_box(
				t_vec3 *p1,
				t_vec3 *p2,
				t_vec3 *p3,
				t_bounding_box *bbox);


bool	is_polygon_inside_bounding_box(
			t_bounding_box *bbox,
			t_object_polygon *polygon)
{
	if (polygon->type == OBJF_TRIANGLE)
	{
		return (is_triangle_inside_object_bounding_box(
					&polygon->value.as_objf_triangle.point1,
					&polygon->value.as_objf_triangle.point2,
					&polygon->value.as_objf_triangle.point3,
					bbox));
	}
	if (polygon->type == OBJF_RECTANGLE)
	{
		return (is_triangle_inside_object_bounding_box(
					&polygon->value.as_objf_rectangle.point1,
					&polygon->value.as_objf_rectangle.point2,
					&polygon->value.as_objf_rectangle.point3,
					bbox)
				|| is_triangle_inside_object_bounding_box(
					&polygon->value.as_objf_rectangle.point1,
					&polygon->value.as_objf_rectangle.point3,
					&polygon->value.as_objf_rectangle.point4,
					bbox));
	}
	return (false);
}


static bool is_triangle_inside_object_bounding_box(
				t_vec3 *p1,
				t_vec3 *p2,
				t_vec3 *p3,
				t_bounding_box *bbox)

{
	float boxcenter[3];
	float boxhalfsize[3];
	float triverts[3][3];

	boxhalfsize[0] = bbox->half_width;
	boxhalfsize[1] = bbox->half_height;
	boxhalfsize[2] = bbox->half_depth;

	boxcenter[0] = bbox->center.x;
	boxcenter[1] = bbox->center.y;
	boxcenter[2] = bbox->center.z;

	triverts[0][0] = p1->x;
	triverts[0][1] = p1->y;
	triverts[0][2] = p1->z;

	triverts[1][0] = p2->x;
	triverts[1][1] = p2->y;
	triverts[1][2] = p2->z;

	triverts[2][0] = p3->x;
	triverts[2][1] = p3->y;
	triverts[2][2] = p3->z;

	return (triBoxOverlap(boxcenter, boxhalfsize, triverts));
}
