/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_intersection_with_sphere_from_inside.c        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouba <aderouba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 16:25:15 by tdubois           #+#    #+#             */
/*   Updated: 2023/06/22 18:48:07 by aderouba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt/app/app.h"

#include <stdbool.h>
#include <math.h>

#include "minirt/app/utils/geometry/geometry.h"

/**
 * Test ray-sphere intersection. Algorithm is derived from
 * https://en.wikipedia.org/wiki/Line%E2%80%93sphere_intersection
 *
 * @param[in] ray Normalized ray
 * @param[in] sphere
 * @param[out] distance From ray origin to intersection point
 * @returns Wether ray intersects with sphere
 */
bool	test_intersection_with_sphere_from_inside(
			t_ray const *ray,
			t_sphere const *sphere,
			t_intersect_info *intersect_info)
{
	t_vec3	vec;
	float	dot;
	float	nabla;

	vec3_substract_into(&vec, &ray->pos, &sphere->pos);
	dot = vec3_dot(&ray->vec, &vec);
	nabla = powf(dot, 2.0f) - vec3_dot(&vec, &vec) + sphere->radius2;
	if (nabla < 0)
		return (false);
	nabla = sqrtf(nabla);
	intersect_info->sub_part_id = 0;
	intersect_info->distance = -dot + nabla;
	if (intersect_info->distance >= 0)
		return (true);
	return (false);
}
