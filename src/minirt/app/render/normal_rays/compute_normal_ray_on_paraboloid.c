/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compute_normal_ray_on_paraboloid.c                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dguillau <dguillau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 08:51:19 by damien            #+#    #+#             */
/*   Updated: 2025/01/17 14:29:15 by dguillau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt/app/app.h"

#include "minirt/app/scene/scene.h"
#include "minirt/app/utils/geometry/geometry.h"

void	compute_normal_ray_on_paraboloid(
				t_object const *paraboloid,
				t_ray const *ray,
				t_intersect_info const *intersect_info,
				t_ray *normal)
{
	t_paraboloid const *const	geometry = &paraboloid->value.as_paraboloid;
	t_vec3						d;
	t_vec3						s;
	t_vec3						vec;
	float						height_on_para;

	normal->pos = ray->pos;
	vec3_linear_transform(&normal->pos, intersect_info->distance, &ray->vec);
	vec = normal->pos;
	vec3_substract(&vec, &geometry->pos);
	height_on_para = vec3_dot(&vec, &geometry->dir);
	d = geometry->dir;
	vec3_scale(&d, height_on_para + geometry->k);
	vec3_substract_into(&s, &normal->pos, &geometry->pos);
	vec3_substract_into(&normal->vec, &s, &d);
	if (intersect_info->sub_part_id == 1)
		vec3_scale(&normal->vec, -1);
	vec3_normalize(&normal->vec);
}
