/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compute_normal_base_cube.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auguste <auguste@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 16:44:47 by aderouba          #+#    #+#             */
/*   Updated: 2024/03/17 22:28:42 by auguste          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt/app/app.h"

#include "minirt/app/utils/geometry/geometry.h"

static void	set_normal_base(
				t_vec3 normal_base[3],
				t_plane const *px,
				t_plane const *py,
				t_plane const *pz);

void	compute_normal_base_cube(
				t_vec3 normal_base[3],
				t_cube const *cube,
				t_intersect_info const *intersect_info)
{
	if (intersect_info->sub_part_id == 0)
		set_normal_base(normal_base, &cube->back, &cube->top, &cube->right);
	else if (intersect_info->sub_part_id == 1)
		set_normal_base(normal_base, &cube->front, &cube->top, &cube->left);
	else if (intersect_info->sub_part_id == 2)
		set_normal_base(normal_base, &cube->right, &cube->top, &cube->back);
	else if (intersect_info->sub_part_id == 3)
		set_normal_base(normal_base, &cube->right, &cube->bot, &cube->front);
	else if (intersect_info->sub_part_id == 4)
		set_normal_base(normal_base, &cube->right, &cube->top, &cube->front);
	else
		set_normal_base(normal_base, &cube->left, &cube->top, &cube->back);
}

//#include <stdio.h>
static void	set_normal_base(
				t_vec3 normal_base[3],
				t_plane const *px,
				t_plane const *py,
				t_plane const *pz)
{
	normal_base[0] = px->normal;
	normal_base[1] = py->normal;
	normal_base[2] = pz->normal;
	//if (normal_base[2].x >= 0.9f)
	//	printf("RECT\n|% .2f, % .2f, % .2f|\n"
	//				"|% .2f, % .2f, % .2f|\n"
	//				"|% .2f, % .2f, % .2f|\n",
	//			normal_base[0].x, normal_base[0].y, normal_base[0].z,
	//			normal_base[1].x, normal_base[1].y, normal_base[1].z,
	//			normal_base[2].x, normal_base[2].y, normal_base[2].z);
}
