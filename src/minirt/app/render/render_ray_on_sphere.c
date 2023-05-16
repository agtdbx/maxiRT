/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_ray_on_sphere.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdubois <tdubois@student.42angouleme.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 10:06:32 by tdubois           #+#    #+#             */
/*   Updated: 2023/05/16 11:52:57 by tdubois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt/app/app.h>

int	render_ray_on_sphere(
		t_sphere const *sphere,
		t_ray const *ray,
		float distance)
{
	t_ray	normal;

	normal.pos = ray->pos;
	vec3_linear_transform(&normal.pos, distance, &ray->vec);
	vec3_substract_into(&normal.vec, &normal.pos, &sphere->pos);
	vec3_normalize(&normal.vec);

	t_vec3	reverse_ray = ray->vec;
	vec3_scale(&reverse_ray, -1.0f);

	float intensity = vec3_dot(&normal.vec, &reverse_ray);
	(void) sphere;
	(void) ray;
	(void) distance;
	return (0
		| ((int32_t)(255 * intensity) << 24)
		| ((int32_t)(255 * intensity) << 16)
		| ((int32_t)(255 * intensity) << 8)
		| 255);
}
