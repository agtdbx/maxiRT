/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   point_inside_object_bounding_box_bonus.c           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auguste <auguste@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 22:32:26 by auguste           #+#    #+#             */
/*   Updated: 2024/03/18 22:44:22 by auguste          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt/app/app_bonus.h"

#include <stdbool.h>
#include <math.h>

#include "minirt/app/utils/geometry/geometry_bonus.h"

static bool	is_in_bound(
				float min,
				float max,
				float nb);

bool	point_inside_object_bounding_box(
			t_object_bounding_box *bounding_box,
			t_vec3 *point)
{
	if (!is_in_bound(
			bounding_box->min_x,
			bounding_box->max_x,
			point->x))
		return (false);
	if (!is_in_bound(
			bounding_box->min_y,
			bounding_box->max_y,
			point->y))
		return (false);
	if (!is_in_bound(
			bounding_box->min_z,
			bounding_box->max_z,
			point->z))
		return (false);
	return (true);
}


static bool	is_in_bound(
				float min,
				float max,
				float nb)
{
	return (min <= nb && nb <= max);
}
