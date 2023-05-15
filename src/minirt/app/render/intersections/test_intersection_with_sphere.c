/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_intersection_with_sphere.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdubois <tdubois@student.42angouleme.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 16:25:15 by tdubois           #+#    #+#             */
/*   Updated: 2023/05/15 17:08:29 by tdubois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt/app/app.h>

#include <minirt/utils/geometry.h>
#include <stdbool.h>
#include <math.h>

//TODO: create vec3_substract

/**
 * Test ray-sphere intersection. Algorithm is derived from
 * https://en.wikipedia.org/wiki/Line%E2%80%93sphere_intersection
 *
 * @param[in] ray Normalized ray
 * @param[in] sphere
 * @param[out] distance From ray origin to intersection point
 * @returns Wether ray intersects with sphere
 */
bool	test_intersection_with_sphere(
			t_ray const *ray,
			t_sphere const *sphere,
			float *distance)
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
	*distance = -dot - nabla;
	if (*distance > 0)
		return (true);
	*distance = -dot + nabla;
	if (*distance > 0)
		return (true);
	return (false);
}
