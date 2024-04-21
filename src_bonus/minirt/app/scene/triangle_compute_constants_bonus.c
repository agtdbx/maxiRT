/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triangle_compute_constants_bonus.c                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auguste <auguste@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 19:51:32 by aderouba          #+#    #+#             */
/*   Updated: 2024/04/21 12:36:50 by auguste          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt/app/scene/scene_bonus.h"

#include <math.h>

#include "minirt/app/utils/geometry/geometry_bonus.h"
#include "minirt/app/utils/space_partition/space_partition.h"

static void	_compute_triangle_pixel_pos_constants(
				t_triangle *triangle,
				float ax, float ay,
				float bx, float by,
				float cx, float cy,
				int pixel_pos_base);
static void	_compute_object_triangle_bounding_box(
				t_bounding_box *bbox,
				t_triangle *triangle);
/**
 * Compute constants from triangle properties to facilitate further calculations
 * @param[out] triangle
 */
void	triangle_compute_constants(
			t_triangle *triangle,
			t_bounding_box *bbox)
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
	_compute_object_triangle_bounding_box(bbox, triangle);
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

static void	_compute_object_triangle_bounding_box(
				t_bounding_box *bbox,
				t_triangle *triangle)
{
	bbox->min_x = triangle->point1.x;
	bbox->max_x = triangle->point1.x;
	bbox->min_y = triangle->point1.y;
	bbox->max_y = triangle->point1.y;
	bbox->min_z = triangle->point1.z;
	bbox->max_z = triangle->point1.z;

	set_min_max(&bbox->min_x, &bbox->max_x, &triangle->point2.x);
	set_min_max(&bbox->min_y, &bbox->max_y, &triangle->point2.y);
	set_min_max(&bbox->min_z, &bbox->max_z, &triangle->point2.z);

	set_min_max(&bbox->min_x, &bbox->max_x, &triangle->point3.x);
	set_min_max(&bbox->min_y, &bbox->max_y, &triangle->point3.y);
	set_min_max(&bbox->min_z, &bbox->max_z, &triangle->point3.z);

	compute_bounding_box_constants(bbox);
}
