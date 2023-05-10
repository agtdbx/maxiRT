/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_intersection_with_sphere.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdubois <tdubois@student.42angouleme.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 16:25:15 by tdubois           #+#    #+#             */
/*   Updated: 2023/05/10 17:28:18 by tdubois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt/utils/geometry.h"
#include <minirt/app/app.h>

#include <stdbool.h>
#include <math.h>

bool	test_intersection_with_sphere(
			t_ray const *ray,
			t_sphere *const sphere,
			float *distance)
{
	t_vec3	vec_to_center;
	float	a;
	float	b;
	float	c;
	float	quadratic_solution[2];

	vec_to_center = ray->pos;
	vec3_sub(&vec_to_center, &sphere->pos);
	a = vec3_dot(&ray->vec, &ray->vec);
	b = 2.0f * vec3_dot(&vec_to_center, &ray->vec);
	c = vec3_dot(&vec_to_center, &vec_to_center) - sphere->radius2;
	if (solve_quadratic(a, b, c, quadratic_solution) == false)
		return (false);
	*distance = fmin(
			fmax(0.0f, quadratic_solution[0]),
			fmax(0.0f, quadratic_solution[1]));
	return (*distance > 0.0f);
}
