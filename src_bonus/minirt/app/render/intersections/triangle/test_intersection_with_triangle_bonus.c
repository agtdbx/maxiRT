/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_intersection_with_triangle_bonus.c            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auguste <auguste@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 16:25:15 by tdubois           #+#    #+#             */
/*   Updated: 2024/03/08 15:02:54 by auguste          ###   ########.fr       */
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
	(void)ray;
	(void)triangle;
	(void)intersect_info;
	return (false);

	//t_vec3	vec;
	//float	dot;
	//float	nabla;

	//vec3_substract_into(&vec, &ray->pos, &sphere->pos);
	//dot = vec3_dot(&ray->vec, &vec);
	//nabla = powf(dot, 2.0f) - vec3_dot(&vec, &vec) + sphere->radius2;
	//if (nabla < 0)
	//	return (false);
	//nabla = sqrtf(nabla);
	//intersect_info->sub_part_id = 0;
	//intersect_info->distance = -dot - nabla;
	//if (intersect_info->distance >= 0)
	//	return (true);
	//intersect_info->distance = -dot + nabla;
	//if (intersect_info->distance >= 0)
	//	return (true);
	//return (false);
}
