/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triangle_compute_constants_bonus.c                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auguste <auguste@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 19:51:32 by aderouba          #+#    #+#             */
/*   Updated: 2024/03/17 00:20:15 by auguste          ###   ########.fr       */
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
	vec3_substract_into(&triangle->edge1, &triangle->point2, &triangle->point1);
	vec3_substract_into(&triangle->edge2, &triangle->point3, &triangle->point1);
	triangle->normal.x = (triangle->edge1.y * triangle->edge2.z)
						- (triangle->edge1.z * triangle->edge2.y);
	triangle->normal.y = (triangle->edge1.z * triangle->edge2.x)
						- (triangle->edge1.x * triangle->edge2.z);
	triangle->normal.z = (triangle->edge1.x * triangle->edge2.y)
						- (triangle->edge1.y * triangle->edge2.x);
	vec3_normalize(&triangle->normal);
}
