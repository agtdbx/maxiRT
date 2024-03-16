/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_file_compute_constants_bonus.c              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auguste <auguste@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 19:51:32 by aderouba          #+#    #+#             */
/*   Updated: 2024/03/16 11:04:29 by auguste          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt/app/scene/scene_bonus.h"

#include <math.h>
#include <stdio.h>

#include "minirt/app/utils/geometry/geometry_bonus.h"

/**
 * Compute constants from cube properties to facilitate further calculations
 * @param[out] cube
 */
void	object_file_compute_constants(
			t_object_file *objf)
{
	vec3_cross(&objf->x_axis, &objf->y_axis, &objf->z_axis);
	vec3_normalize(&objf->x_axis);
	vec3_normalize(&objf->y_axis);
	vec3_normalize(&objf->z_axis);

	//compute bounding box
}
