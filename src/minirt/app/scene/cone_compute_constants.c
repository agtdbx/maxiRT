/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone_compute_constants.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouba <aderouba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 19:51:32 by aderouba          #+#    #+#             */
/*   Updated: 2023/07/19 19:42:24 by aderouba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt/app/scene/scene.h"

#include <math.h>
#include <stdio.h>

#include "minirt/app/utils/geometry/geometry.h"

/**
 * Compute constants from cone properties to facilitate further calculations
 * @param[out] cone
 */
void	cone_compute_constants(
			t_cone *cone)
{
	vec3_normalize(&cone->axis);
	cone->radius = cone->diameter / 2.0f;
	cone->radius2 = cone->radius * cone->radius;
	cone->end.pos = cone->pos;
	vec3_linear_transform(
		&cone->end.pos, cone->height, &cone->axis);
	cone->end.normal = cone->axis;
	cone->end.rev_normal = cone->axis;
	vec3_scale(&cone->end.rev_normal, -1.0f);
	cone->ratio = cone->radius / cone->height;
	cone->ratio = 1.0 + (cone->ratio * cone->ratio);
}
