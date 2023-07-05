/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compute_normal_ray_on_sphere.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouba <aderouba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 20:38:43 by aderouba          #+#    #+#             */
/*   Updated: 2023/07/05 20:39:26 by aderouba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt/app/app.h"

#include "minirt/app/scene/scene.h"
#include "minirt/app/utils/geometry/geometry.h"

void	compute_normal_ray_on_sphere(
				t_object const *sphere,
				t_ray const *ray,
				float distance,
				t_ray *normal)
{
	t_sphere const *const	geometry = &sphere->value.as_sphere;

	normal->pos = ray->pos;
	vec3_linear_transform(&normal->pos, distance, &ray->vec);
	vec3_substract_into(&normal->vec, &normal->pos, &geometry->pos);
	vec3_normalize(&normal->vec);
}
