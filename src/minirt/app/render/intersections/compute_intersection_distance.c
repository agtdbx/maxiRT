/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compute_intersection_distance.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damien <damien@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 20:30:06 by aderouba          #+#    #+#             */
/*   Updated: 2025/01/16 23:42:17 by damien           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt/app/app.h"

#include <stdbool.h>
#include <math.h>

#include "minirt/app/utils/geometry/geometry.h"

bool	compute_intersection_distance(
				t_intersect_info *intersect_info,
				float abc[3])
{
	float	discriminant;
	float	denom = 0.0f;

	discriminant = (abc[1] * abc[1]) - (4 * abc[0] * abc[2]);
	if (discriminant < 0)
		return (false);
	else if (discriminant == 0)
	{
		intersect_info->distance = -abc[1] / (abc[0] * 2.0f);
		if (intersect_info->distance < 0.0f)
			return (false);
	}
	else
	{
		discriminant = sqrtf(discriminant);
		denom = 1.0f / (abc[0] * 2.0f);
		intersect_info->distance = (-abc[1] - discriminant) * denom;
		if (intersect_info->distance < 0.0f)
		{
			intersect_info->distance = (-abc[1] + discriminant) * denom;
			if (intersect_info->distance < 0.0f)
				return (false);
		}
	}
	intersect_info->distance2 = (-abc[1] + discriminant) * denom;
	return (true);
}
