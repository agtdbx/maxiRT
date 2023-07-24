/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compute_normal_base_cube.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouba <aderouba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 16:44:47 by aderouba          #+#    #+#             */
/*   Updated: 2023/07/06 17:08:43 by aderouba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt/app/app_bonus.h"

#include "minirt/app/utils/geometry/geometry_bonus.h"

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

static void	set_normal_base(
				t_vec3 normal_base[3],
				t_plane const *px,
				t_plane const *py,
				t_plane const *pz)
{
	normal_base[0] = px->normal;
	normal_base[1] = py->normal;
	normal_base[2] = pz->normal;
}
