/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_intersection_with_triangle_bonus.c            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auguste <auguste@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 16:25:15 by tdubois           #+#    #+#             */
/*   Updated: 2024/03/11 17:55:43 by auguste          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt/app/app_bonus.h"

#include <stdbool.h>
#include <math.h>

#include "minirt/app/utils/geometry/geometry_bonus.h"

/**
 * Test ray-triangle intersection. Algorithm is derived from
 * https://hugi.scene.org/online/hugi24/coding%20graphics
 * %20chris%20dragan%20raytracing%20shapes.htm
 *
 * @param[in] ray Normalized ray
 * @param[in] triangle
 * @param[out] distance From ray origin to intersection point
 * @returns Wether ray intersects with sphere
 */
bool	test_intersection_with_triangle(
			t_ray const *ray,
			t_triangle const *triangle,
			t_intersect_info *intersect_info)
{
	t_vec3	vec;
	t_vec3	intersect_point;
	float	denom;
	float	p;
	float	q;

	vec3_substract_into(&vec, &triangle->point1, &ray->pos);
	denom = vec3_dot(&ray->vec, &triangle->normal);
	if (denom < 0.000001f)
	{
		intersect_info->sub_part_id = 0;
		intersect_info->distance = vec3_dot(&vec, &triangle->normal) / denom;
		if (intersect_info->distance < 0.0f)
			return (false);

		// Get the intersection point
		intersect_point = ray->pos;
		vec3_linear_transform(&intersect_point, intersect_info->distance,
								&ray->vec);

		if (triangle->v2.x == 0.0f)
			return (false);

		float	div_part = triangle->v1.y * triangle->v2.x
							- triangle->v1.x * triangle->v2.y;

		if (div_part == 0.0f)
			return (false);

		p = triangle->v2.x * (intersect_point.y - triangle->point1.y) -
			triangle->v2.y * (intersect_point.x - triangle->point1.x);
		p = p / div_part;

		if (p < 0.0f || p > 1.0f)
			return (false);

		q = intersect_point.x - triangle->point1.x - (triangle->v1.x * p);
		q = q / triangle->v2.x;

		if (q < 0.0f || q > 1.0f)
			return (false);

		if (q + p < 0.0f || q + p > 1.0f)
			return (false);
		return (true);
	}
	else if (denom > -0.000001f)
	{
		intersect_info->sub_part_id = 1;
		intersect_info->distance = vec3_dot(&vec, &triangle->normal) / denom;
		if (intersect_info->distance < 0.0f)
			return (false);

		// Get the intersection point
		intersect_point = ray->pos;
		vec3_linear_transform(&intersect_point, intersect_info->distance,
								&ray->vec);

		if (triangle->v2.x == 0.0f)
			return (false);

		float	div_part = triangle->v1.y * triangle->v2.x
							- triangle->v1.x * triangle->v2.y;

		if (div_part == 0.0f)
			return (false);

		p = triangle->v2.x * (intersect_point.y - triangle->point1.y) -
			triangle->v2.y * (intersect_point.x - triangle->point1.x);
		p = p / div_part;

		if (p < 0.0f || p > 1.0f)
			return (false);

		q = intersect_point.x - triangle->point1.x - (triangle->v1.x * p);
		q = q / triangle->v2.x;

		if (q < 0.0f || q > 1.0f)
			return (false);

		if (q + p < 0.0f || q + p > 1.0f)
			return (false);
		return (true);
	}
	return (false);
}

/*
[ Px-Cx ] = [ V1.x V2.x ] * [ p ]
[ Py-Cy ]   [ V1.y V2.y ]   [ q ]


Px-Cx = V1.x * p + V2.x * q
Py-Cy = V1.y * p + V2.y * q

*/
