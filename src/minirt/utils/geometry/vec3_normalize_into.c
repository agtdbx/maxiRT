/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_normalize_into.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdubois <tdubois@student.42angouleme.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 16:38:08 by tdubois           #+#    #+#             */
/*   Updated: 2023/05/11 16:56:41 by tdubois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt/utils/geometry.h>

#include <math.h>

extern inline void	vec3_normalize_into(
						t_vec3 *restrict dst,
						t_vec3 const *restrict src)
{
	float const	magnitude = sqrtf(0
			+ src->x * src->x
			+ src->y * src->y
			+ src->z * src->z);

	dst->x = src->x / magnitude;
	dst->y = src->y / magnitude;
	dst->z = src->z / magnitude;
}
