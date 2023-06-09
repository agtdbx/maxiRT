/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_normalize_into.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdubois <tdubois@student.42angouleme.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 16:38:08 by tdubois           #+#    #+#             */
/*   Updated: 2023/06/09 15:47:53 by tdubois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt/app/utils/geometry/geometry.h"

#include <math.h>

extern inline float	vec3_normalize_into(
						t_vec3 *restrict dst,
						t_vec3 const *restrict src)
{
	float	norm;

	if (src->x == 0.0f && src->y == 0.0f && src->z == 0.0f)
		return (0.0f);
	norm = vec3_norm(src);
	dst->x = src->x / norm;
	dst->y = src->y / norm;
	dst->z = src->z / norm;
	return (norm);
}
