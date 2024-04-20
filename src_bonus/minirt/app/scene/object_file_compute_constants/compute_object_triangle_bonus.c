/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compute_object_triangle_bonus.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auguste <auguste@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 22:48:40 by auguste           #+#    #+#             */
/*   Updated: 2024/04/20 17:11:33 by auguste          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt/app/scene/scene_bonus.h"

#include <math.h>

#include "minirt/app/utils/geometry/geometry_bonus.h"

static void	compute_objf_triangle_pixel_pos_constants(
				t_object_triangle *triangle,
				float ax, float ay,
				float bx, float by,
				float cx, float cy,
				int pixel_pos_base);
static void	_compute_object_triangle_bounding_box(
				t_bounding_box *bbox,
				t_object_triangle *triangle);
static void	_set_min_max(
				float *min,
				float *max,
				float *test);

void		compute_objf_triangle(
				t_object_file *objf,
				t_object_triangle *triangle,
				t_bounding_box *bbox)
{
	t_vec3	p2_p1;
	t_vec3	p3_p1;

	// Get points from real vertice
	triangle->point1 = objf->real_vertices[triangle->vertice_1];
	triangle->point2 = objf->real_vertices[triangle->vertice_2];
	triangle->point3 = objf->real_vertices[triangle->vertice_3];

	// Compute triangle constants
	vec3_substract_into(&triangle->edge1, &triangle->point2, &triangle->point1);
	vec3_substract_into(&triangle->edge2, &triangle->point3, &triangle->point1);

	vec3_substract_into(&p2_p1, &triangle->point2, &triangle->point1);
	vec3_substract_into(&p3_p1, &triangle->point3, &triangle->point1);
	vec3_cross(&p2_p1, &p3_p1, &triangle->normal);

	vec3_normalize(&triangle->normal);

	// Compute pixel pos constants
	compute_objf_triangle_pixel_pos_constants(
		triangle,
		triangle->point1.x, triangle->point1.y,
		triangle->point2.x, triangle->point2.y,
		triangle->point3.x, triangle->point3.y,
		0);
	if (triangle->div_part == 0.0f)
	{
		compute_objf_triangle_pixel_pos_constants(
		triangle,
		triangle->point1.x, triangle->point1.z,
		triangle->point2.x, triangle->point2.z,
		triangle->point3.x, triangle->point3.z,
		1);
		if (triangle->div_part == 0.0f)
		{
			compute_objf_triangle_pixel_pos_constants(
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

static void	compute_objf_triangle_pixel_pos_constants(
				t_object_triangle *triangle,
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
				t_object_triangle *triangle)
{
	bbox->min_x = triangle->point1.x;
	bbox->max_x = triangle->point1.x;
	bbox->min_y = triangle->point1.y;
	bbox->max_y = triangle->point1.y;
	bbox->min_z = triangle->point1.z;
	bbox->max_z = triangle->point1.z;

	_set_min_max(&bbox->min_x, &bbox->max_x, &triangle->point2.x);
	_set_min_max(&bbox->min_y, &bbox->max_y, &triangle->point2.y);
	_set_min_max(&bbox->min_z, &bbox->max_z, &triangle->point2.z);

	_set_min_max(&bbox->min_x, &bbox->max_x, &triangle->point3.x);
	_set_min_max(&bbox->min_y, &bbox->max_y, &triangle->point3.y);
	_set_min_max(&bbox->min_z, &bbox->max_z, &triangle->point3.z);
}

static void	_set_min_max(
				float *min,
				float *max,
				float *test)
{
	if (*min > *test)
		*min = *test;
	if (*max < *test)
		*max = *test;
}
