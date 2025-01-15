/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triangle_compute_constants.c                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auguste <auguste@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 19:51:32 by aderouba          #+#    #+#             */
/*   Updated: 2024/04/21 12:36:50 by auguste          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt/app/scene/scene.h"

#include <math.h>

#include "minirt/app/utils/geometry/geometry.h"
#include "minirt/app/utils/space_partition/space_partition.h"

static void	_compute_triangle_pixel_pos_constants(
				t_triangle *triangle,
				float ax, float ay,
				float bx, float by,
				float cx, float cy,
				int pixel_pos_base);

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

	// Compute pixel pos constants
	_compute_triangle_pixel_pos_constants(
		triangle,
		triangle->point1.x, triangle->point1.y,
		triangle->point2.x, triangle->point2.y,
		triangle->point3.x, triangle->point3.y,
		0);
	if (triangle->div_part == 0.0f)
	{
		_compute_triangle_pixel_pos_constants(
		triangle,
		triangle->point1.x, triangle->point1.z,
		triangle->point2.x, triangle->point2.z,
		triangle->point3.x, triangle->point3.z,
		1);
		if (triangle->div_part == 0.0f)
		{
			_compute_triangle_pixel_pos_constants(
			triangle,
			triangle->point1.z, triangle->point1.y,
			triangle->point2.z, triangle->point2.y,
			triangle->point3.z, triangle->point3.y,
			2);
			if (triangle->div_part == 0.0f)
				triangle->pixel_pos_base = -1;
		}
	}
}


static void	_compute_triangle_pixel_pos_constants(
				t_triangle *triangle,
				float ax, float ay,
				float bx, float by,
				float cx, float cy,
				int pixel_pos_base)
{
	float	ACy;

	triangle->BCy = by - cy;
	triangle->CBx = cx - bx;
	ACy = ay - cy;
	triangle->CAy = cy - ay;
	triangle->ACx = ax - cx;

	triangle->div_part = (triangle->BCy * triangle->ACx)
						+ (triangle->CBx * ACy);
	if (triangle->div_part != 0.0f)
	{
		triangle->pixel_pos_base = pixel_pos_base;
		triangle->div_part = 1.0f / triangle->div_part;
	}
}
