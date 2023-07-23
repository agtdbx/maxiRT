/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compute_normal_ray_on_cube.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouba <aderouba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 20:40:29 by aderouba          #+#    #+#             */
/*   Updated: 2023/07/05 20:40:45 by aderouba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt/app/app_bonus.h"

#include "minirt/app/scene/scene_bonus.h"
#include "minirt/app/utils/geometry/geometry_bonus.h"

void	compute_normal_ray_on_cube(
				t_object const *cube,
				t_ray const *ray,
				t_intersect_info const *intersect_info,
				t_ray *normal)
{
	t_cube const *const	geometry = &cube->value.as_cube;

	normal->pos = ray->pos;
	vec3_linear_transform(&normal->pos, intersect_info->distance, &ray->vec);
	if (intersect_info->sub_part_id == 0)
		normal->vec = geometry->right.normal;
	else if (intersect_info->sub_part_id == 1)
		normal->vec = geometry->left.normal;
	else if (intersect_info->sub_part_id == 2)
		normal->vec = geometry->top.normal;
	else if (intersect_info->sub_part_id == 3)
		normal->vec = geometry->bot.normal;
	else if (intersect_info->sub_part_id == 4)
		normal->vec = geometry->front.normal;
	else
		normal->vec = geometry->back.normal;
}
