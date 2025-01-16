/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compute_normal_ray_on_paraboloid.c                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damien <damien@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 08:51:19 by damien            #+#    #+#             */
/*   Updated: 2025/01/16 23:45:12 by damien           ###   ########.fr       */
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
	t_vec3						p;
	t_vec3						d;
	t_vec3						s;
	t_vec3						vec;
	float						height_on_para;
	float						dot;

	p = ray->pos;
	normal->pos = ray->pos;
	vec3_linear_transform(&normal->pos, intersect_info->distance, &ray->vec);
	vec3_linear_transform(&p, intersect_info->distance, &ray->vec);
	vec3_substract_into(&s, &p, &geometry->pos);
	vec3_substract_into(&vec, &p, &geometry->pos);
	height_on_para = vec3_dot(&vec, &geometry->dir);
	d = geometry->dir;
	vec3_scale(&d, height_on_para + geometry->k);
	vec3_substract_into(&normal->vec, &s, &d);
	vec3_normalize(&normal->vec);
	dot = vec3_dot(&normal->vec, &ray->vec);
	if (dot > 0)
		vec3_scale(&normal->vec, -1);
}
