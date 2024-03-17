/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compute_normal_base_object_file_bonus.c            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auguste <auguste@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 16:44:47 by aderouba          #+#    #+#             */
/*   Updated: 2024/03/17 22:31:28 by auguste          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt/app/app_bonus.h"

#include "minirt/app/utils/geometry/geometry_bonus.h"

static void	compute_normal_base_object_triangle(
				t_vec3 normal_base[3]);
static void	compute_normal_base_object_rectangle(
				t_vec3 normal_base[3],
				t_object_rectangle const *rectangle);

void	compute_normal_base_object_file(
				t_vec3 normal_base[3],
				t_object_file const *objf,
				t_intersect_info const *intersect_info)
{
	t_object_polygon	*const polygon = &objf->polygons[
											intersect_info->sub_part_id];

	if (polygon->type == OBJF_TRIANGLE)
		compute_normal_base_object_triangle(normal_base);
	else if (polygon->type == OBJF_RECTANGLE)
		compute_normal_base_object_rectangle(normal_base,
			&polygon->value.as_objf_rectangle);
}

static void	compute_normal_base_object_triangle(
				t_vec3 normal_base[3])
{
	if (normal_base[2].x != 0.0f || normal_base[2].y != 0.0f)
		normal_base[1] = (t_vec3){normal_base[2].y, -normal_base[2].x, 0.0f};
	else
		normal_base[1] = (t_vec3){0.0f, -1.0f, 0.0f};
	vec3_cross(&normal_base[2], &normal_base[1], &normal_base[0]);
	vec3_normalize(&normal_base[0]);
	vec3_normalize(&normal_base[1]);
}

//#include <stdio.h>
static void	compute_normal_base_object_rectangle(
				t_vec3 normal_base[3],
				t_object_rectangle const *rectangle)
{
	vec3_scale_into(&normal_base[0], &rectangle->x_axis, -1.0f);
	//normal_base[0] = rectangle->x_axis;
	//vec3_scale_into(&normal_base[1], &rectangle->y_axis, -1.0f);
	normal_base[1] = rectangle->y_axis;
	normal_base[2] = rectangle->normal;
	//if (normal_base[2].x >= 0.9f)
	//	printf("RECT\n|% .2f, % .2f, % .2f|\n"
	//				"|% .2f, % .2f, % .2f|\n"
	//				"|% .2f, % .2f, % .2f|\n",
	//			normal_base[0].x, normal_base[0].y, normal_base[0].z,
	//			normal_base[1].x, normal_base[1].y, normal_base[1].z,
	//			normal_base[2].x, normal_base[2].y, normal_base[2].z);
}
