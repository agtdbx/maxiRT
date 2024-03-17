/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triangle_compute_constants_bonus.c                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auguste <auguste@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 19:51:32 by aderouba          #+#    #+#             */
/*   Updated: 2024/03/17 12:14:11 by auguste          ###   ########.fr       */
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
	float	ACy;

	vec3_substract_into(&triangle->edge1, &triangle->point2, &triangle->point1);
	vec3_substract_into(&triangle->edge2, &triangle->point3, &triangle->point1);
	triangle->normal.x = (triangle->edge1.y * triangle->edge2.z)
						- (triangle->edge1.z * triangle->edge2.y);
	triangle->normal.y = (triangle->edge1.z * triangle->edge2.x)
						- (triangle->edge1.x * triangle->edge2.z);
	triangle->normal.z = (triangle->edge1.x * triangle->edge2.y)
						- (triangle->edge1.y * triangle->edge2.x);
	vec3_normalize(&triangle->normal);

	triangle->BCy = triangle->point2.y - triangle->point3.y;
	triangle->CBx = triangle->point3.x - triangle->point2.x;
	ACy = triangle->point1.y - triangle->point3.y;
	triangle->CAy = triangle->point3.y - triangle->point1.y;
	triangle->ACx = triangle->point1.x - triangle->point3.x;

	triangle->div_part = (triangle->BCy *triangle-> ACx)
						+ (triangle->CBx * ACy);
	if (triangle->div_part != 0.0f)
		triangle->div_part = 1.0f / triangle->div_part;
}
