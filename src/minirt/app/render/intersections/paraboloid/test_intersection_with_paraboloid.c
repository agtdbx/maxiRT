/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_intersection_with_paraboloid.c                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damien <damien@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 23:02:04 by damien            #+#    #+#             */
/*   Updated: 2025/01/16 23:42:39 by damien           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt/app/app.h"
#include "minirt/app/scene/scene.h"
#include "minirt/app/utils/geometry/geometry.h"

#include <math.h>

bool	test_intersection_with_paraboloid(
			t_ray const *ray,
			t_paraboloid const *para,
			t_intersect_info *intersect_info)
{
	float	abc[3];
	float	dot[2];
	t_vec3	vec;
	t_vec3	p;
	float	height_on_para;

	dot[0] = vec3_dot(&ray->vec, &para->dir);
	vec3_substract_into(&vec, &ray->pos, &para->pos);
	dot[1] = vec3_dot(&vec, &para->dir);
	abc[0] = vec3_dot(&ray->vec, &ray->vec) - (dot[0] * dot[0]);
	abc[1] = (vec3_dot(&ray->vec, &vec) - dot[0] * (dot[1] + 2 * para->k)) * 2;
	abc[2] = vec3_dot(&vec, &vec) - dot[1] * (dot[1] + 4 * para->k);
	if (compute_intersection_distance(intersect_info, abc) == false)
		return (false);
	p = ray->pos;
	vec3_linear_transform(&p, intersect_info->distance, &ray->vec);
	vec3_substract_into(&vec, &p, &para->pos);
	height_on_para = vec3_dot(&vec, &para->dir);
	if (height_on_para > para->k)
	{
		if (intersect_info->distance2 < 0)
			return (false);
		p = ray->pos;
		vec3_linear_transform(&p, intersect_info->distance2, &ray->vec);
		vec3_substract_into(&vec, &p, &para->pos);
		height_on_para = vec3_dot(&vec, &para->dir);
		if (height_on_para > para->k)
			return (false);
		intersect_info->distance = intersect_info->distance2;
	}
	return (true);
}
