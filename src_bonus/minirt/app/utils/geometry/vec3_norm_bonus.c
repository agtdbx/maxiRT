/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_norm.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdubois <tdubois@student.42angouleme.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 16:10:21 by tdubois           #+#    #+#             */
/*   Updated: 2023/06/09 15:02:46 by tdubois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt/app/utils/geometry/geometry_bonus.h"

#include <math.h>

extern inline float	vec3_norm(
						t_vec3 const *vec)
{
	return (
		sqrtf(powf(vec->x, 2.0f) + powf(vec->y, 2.0f) + powf(vec->z, 2.0f)));
}
