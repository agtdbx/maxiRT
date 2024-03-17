/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_object_file_pixel_pos_bonus.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auguste <auguste@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 15:49:28 by aderouba          #+#    #+#             */
/*   Updated: 2024/03/17 12:19:51 by auguste          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt/app/app_bonus.h"

#include <math.h>

#include "minirt/app/utils/geometry/geometry_bonus.h"

t_vec2	get_object_file_pixel_pos(
					t_object_file const *objf,
					t_ray const *normal,
					t_intersect_info const *intersect_info)
{
	t_vec2						pixel;
	t_object_triangle	*const	triangle =
							&objf->triangles[intersect_info->sub_part_id];
	float const					PCx = normal->pos.x - triangle->point3.x;
	float const					PCy = normal->pos.y - triangle->point3.y;

	if (triangle->div_part == 0.0f)
	{
		pixel.x = 0.0f;
		pixel.y = 0.0f;
		return (pixel);
	}
	pixel.x = ((triangle->BCy * PCx) + (triangle->CBx * PCy)) * triangle->div_part;
	pixel.y = ((triangle->CAy * PCx) + (triangle->ACx * PCy)) * triangle->div_part;
	return (pixel);
}
