/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_ray_on_sphere.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdubois <tdubois@student.42angouleme.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 10:06:32 by tdubois           #+#    #+#             */
/*   Updated: 2023/06/01 13:55:56 by tdubois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt/app/app.h>

int32_t	render_ray_on_sphere(
		t_scene const *scene,
		t_sphere const *sphere,
		t_ray const *ray,
		float distance)
{
	t_ray	normal;
	float	intensity;

	(void) scene;

	normal.pos = ray->pos;
	vec3_linear_transform(&normal.pos, distance, &ray->vec);
	vec3_substract_into(&normal.vec, &normal.pos, &sphere->pos);
	vec3_normalize(&normal.vec);
	intensity = -vec3_dot(&normal.vec, &ray->vec);
	return (255
		| ((int32_t)(sphere->color.r * intensity) << 24)
		| ((int32_t)(sphere->color.g * intensity) << 16)
		| ((int32_t)(sphere->color.b * intensity) << 8));
}
