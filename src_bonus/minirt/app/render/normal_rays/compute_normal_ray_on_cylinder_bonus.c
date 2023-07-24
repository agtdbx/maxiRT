/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compute_normal_ray_on_cylinder.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouba <aderouba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 20:39:40 by aderouba          #+#    #+#             */
/*   Updated: 2023/07/05 20:40:52 by aderouba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt/app/app_bonus.h"

#include "minirt/app/scene/scene_bonus.h"
#include "minirt/app/utils/geometry/geometry_bonus.h"

void	compute_normal_ray_on_cylinder(
				t_object const *cylinder,
				t_ray const *ray,
				t_intersect_info const *intersect_info,
				t_ray *normal)
{
	t_cylinder const *const	geometry = &cylinder->value.as_cylinder;
	t_vec3					vec;
	float					dot[2];
	float					heigth_on_cylinder;

	normal->pos = ray->pos;
	vec3_linear_transform(&normal->pos, intersect_info->distance, &ray->vec);
	if (intersect_info->sub_part_id == 1)
		normal->vec = geometry->bot.normal;
	else if (intersect_info->sub_part_id == 2)
		normal->vec = geometry->top.normal;
	else
	{
		vec3_substract_into(&vec, &ray->pos, &geometry->pos);
		dot[0] = vec3_dot(&ray->vec, &geometry->axis);
		dot[1] = vec3_dot(&vec, &geometry->axis);
		heigth_on_cylinder = dot[0] * intersect_info->distance + dot[1];
		vec = normal->pos;
		vec3_substract(&vec, &geometry->pos);
		normal->vec = geometry->axis;
		vec3_scale(&normal->vec, heigth_on_cylinder);
		vec3_substract(&vec, &normal->vec);
		normal->vec = vec;
		vec3_normalize(&normal->vec);
	}
}
