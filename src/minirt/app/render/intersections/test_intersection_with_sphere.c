/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_intersection_with_sphere.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdubois <tdubois@student.42angouleme.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 16:25:15 by tdubois           #+#    #+#             */
/*   Updated: 2023/05/11 01:40:52 by tdubois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt/app/app.h>

#include <minirt/utils/geometry.h>
#include <stdbool.h>
#include <math.h>

//TODO: normalize thrown rays
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
			t_sphere *const sphere,
			float *distance)
{
	t_vec3	vec;
	float	dot;
	float	nabla;

	vec3_substract(&vec, &ray->pos, &sphere->pos);
	dot = vec3_dot(&ray->vec, &vec);
	nabla = dot * dot - vec3_dot(&vec, &vec) + sphere->radius2;
	if (nabla < 0)
		return (false);
	nabla = sqrtf(nabla);
	*distance = -dot - nabla;
	if (*distance > 0)
	{
		*distance /= vec3_dot(&ray->vec, &ray->vec);
		return (true);
	}
	*distance = -dot + nabla;
	if (*distance > 0)
	{
		*distance /= vec3_dot(&ray->vec, &ray->vec);
		return (true);
	}
	return (false);
}
