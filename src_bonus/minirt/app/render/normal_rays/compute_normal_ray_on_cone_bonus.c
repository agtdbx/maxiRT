/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compute_normal_ray_on_cone.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouba <aderouba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 20:40:10 by aderouba          #+#    #+#             */
/*   Updated: 2023/07/19 19:55:31 by aderouba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt/app/app_bonus.h"

#include "minirt/app/scene/scene_bonus.h"
#include "minirt/app/utils/geometry/geometry_bonus.h"

static float	get_height_in_cone(
					t_cone const *const	geometry,
					t_ray const *ray,
					t_intersect_info const *intersect_info)
{
	t_vec3	vec;
	float	dot[2];
	float	heigth_on_cone;

	vec3_substract_into(&vec, &ray->pos, &geometry->pos);
	dot[0] = vec3_dot(&ray->vec, &geometry->axis);
	dot[1] = vec3_dot(&vec, &geometry->axis);
	heigth_on_cone = dot[0] * intersect_info->distance + dot[1];
	return (heigth_on_cone);
}

void	compute_normal_ray_on_cone(
				t_object const *cone,
				t_ray const *ray,
				t_intersect_info const *intersect_info,
				t_ray *normal)
{
	t_cone const *const	geometry = &cone->value.as_cone;
	float				heigth_on_cone;
	t_vec3				vec;

	normal->pos = ray->pos;
	vec3_linear_transform(&normal->pos, intersect_info->distance, &ray->vec);
	if (intersect_info->sub_part_id == 1)
		normal->vec = geometry->end.normal;
	else
	{
		heigth_on_cone = get_height_in_cone(geometry, ray, intersect_info);
		vec = normal->pos;
		vec3_substract(&vec, &geometry->pos);
		normal->vec = geometry->axis;
		vec3_scale(&normal->vec, heigth_on_cone * geometry->ratio);
		vec3_substract(&vec, &normal->vec);
		normal->vec = vec;
		vec3_normalize(&normal->vec);
	}
}
