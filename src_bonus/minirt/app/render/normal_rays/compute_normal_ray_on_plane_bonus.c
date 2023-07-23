/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compute_normal_ray_on_plane.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouba <aderouba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 20:39:11 by aderouba          #+#    #+#             */
/*   Updated: 2023/07/05 20:39:23 by aderouba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt/app/app_bonus.h"

#include "minirt/app/scene/scene_bonus.h"
#include "minirt/app/utils/geometry/geometry_bonus.h"

void	compute_normal_ray_on_plane(
				t_object const *plane,
				t_ray const *ray,
				t_intersect_info const *intersect_info,
				t_ray *normal)
{
	t_plane const *const	geometry = &plane->value.as_plane;

	normal->pos = ray->pos;
	vec3_linear_transform(&normal->pos, intersect_info->distance, &ray->vec);
	if (intersect_info->sub_part_id == 0)
		normal->vec = geometry->normal;
	else
		normal->vec = geometry->rev_normal;
}
