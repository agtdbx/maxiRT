/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_intersection_with_plane.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouba <aderouba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 16:25:15 by tdubois           #+#    #+#             */
/*   Updated: 2023/07/06 18:12:16 by aderouba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt/app/app_bonus.h"

#include <stdbool.h>
#include <math.h>

#include "minirt/app/utils/geometry/geometry_bonus.h"

/**
 * Test ray-sphere intersection. Algorithm is derived from
 * https://hugi.scene.org/online/hugi24/
 * coding%20graphics%20chris%20dragan%20\raytracing%20shapes.htm
 *
 * @param[in] ray Normalized ray
 * @param[in] sphere
 * @param[out] distance From ray origin to intersection point
 * @returns Wether ray intersects with sphere
 */
bool	test_intersection_with_plane(
			t_ray const *ray,
			t_plane const *plane,
			t_intersect_info *intersect_info)
{
	t_vec3	vec;
	float	denom;

	vec3_substract_into(&vec, &plane->pos, &ray->pos);
	denom = vec3_dot(&ray->vec, &plane->normal);
	if (denom < 0.000001f)
	{
		intersect_info->sub_part_id = 0;
		intersect_info->distance = vec3_dot(&vec, &plane->normal) / denom;
		if (intersect_info->distance < 0.0f)
			return (false);
		return (true);
	}
	else if (denom > -0.000001f)
	{
		intersect_info->sub_part_id = 1;
		intersect_info->distance
			= vec3_dot(&vec, &plane->rev_normal) / (-denom);
		if (intersect_info->distance < 0.0f)
			return (false);
		return (true);
	}
	return (false);
}
