/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compute_normal_ray_on_object_file.c          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auguste <auguste@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 20:39:11 by aderouba          #+#    #+#             */
/*   Updated: 2024/03/17 20:09:48 by auguste          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt/app/app.h"

#include "minirt/app/scene/scene.h"
#include "minirt/app/utils/geometry/geometry.h"

void	compute_normal_ray_on_object_file(
				t_object const *object_file,
				t_ray const *ray,
				t_intersect_info const *intersect_info,
				t_ray *normal)
{
	t_object_file const *const	geometry = &object_file->value.as_object_file;

	normal->pos = ray->pos;
	vec3_linear_transform(&normal->pos, intersect_info->distance, &ray->vec);
	if (geometry->polygons[intersect_info->sub_part_id].type == OBJF_TRIANGLE)
		normal->vec = geometry->polygons[intersect_info->sub_part_id]
						.value.as_objf_triangle.normal;
	else if (geometry->polygons[intersect_info->sub_part_id].type == OBJF_RECTANGLE)
		normal->vec = geometry->polygons[intersect_info->sub_part_id]
						.value.as_objf_rectangle.normal;
}
