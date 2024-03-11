/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triangle_compute_constants_bonus.c                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auguste <auguste@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 19:51:32 by aderouba          #+#    #+#             */
/*   Updated: 2024/03/11 15:59:07 by auguste          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt/app/scene/scene_bonus.h"

#include <math.h>

#include "minirt/app/utils/geometry/geometry_bonus.h"

/**
 * Compute constants from triangle properties to facilitate further calculations
 * @param[out] triangle
 */
void	triangle_compute_constants(
			t_triangle *triangle)
{
	vec3_substract_into(&triangle->v1, &triangle->point2, &triangle->point1);
	vec3_substract_into(&triangle->v2, &triangle->point3, &triangle->point1);
	triangle->normal.x = (triangle->v1.y * triangle->v2.z)
						- (triangle->v1.z * triangle->v2.y);
	triangle->normal.y = (triangle->v1.z * triangle->v2.x)
						- (triangle->v1.x * triangle->v2.z);
	triangle->normal.z = (triangle->v1.x * triangle->v2.y)
						- (triangle->v1.y * triangle->v2.x);
	vec3_normalize(&triangle->normal);
}
