/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compute_normal_base_cone.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouba <aderouba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 16:42:54 by aderouba          #+#    #+#             */
/*   Updated: 2023/07/06 16:46:13 by aderouba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt/app/app_bonus.h"

#include "minirt/app/utils/geometry/geometry_bonus.h"

void	compute_normal_base_cone(
				t_vec3 normal_base[3],
				t_cone const *cone,
				t_intersect_info const *intersect_info)
{
	if (intersect_info->sub_part_id == 1)
		compute_normal_base_plane(normal_base);
	else
	{
		vec3_normalize(&normal_base[0]);
		vec3_scale(&normal_base[0], -1.0f);
		normal_base[1] = cone->axis;
		vec3_scale(&normal_base[1], -1.0f);
	}
}
