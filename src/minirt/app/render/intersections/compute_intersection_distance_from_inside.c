/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compute_intersection_distance_from_inside.c        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouba <aderouba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 20:32:07 by aderouba          #+#    #+#             */
/*   Updated: 2023/07/19 20:32:48 by aderouba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt/app/app.h"

#include <stdbool.h>
#include <math.h>

#include "minirt/app/utils/geometry/geometry.h"

bool	compute_intersection_distance_from_inside(
				t_intersect_info *intersect_info,
				float abc[3])
{
	float	discriminant;
	float	denom;

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
		intersect_info->distance = (-abc[1] + discriminant) * denom;
		if (intersect_info->distance < 0.0f)
			return (false);
	}
	return (true);
}
