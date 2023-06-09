/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_substract_into.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdubois <tdubois@student.42angouleme.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 12:03:03 by tdubois           #+#    #+#             */
/*   Updated: 2023/06/09 14:59:54 by tdubois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt/app/utils/geometry/geometry.h"

/**
 * Stores result of lhs - rhs into dst.
 * @param[out] dst
 * @param[in] lhs
 * @param[in] rhs
 */
extern inline void	vec3_substract_into(
						t_vec3 *restrict dst,
						t_vec3 const *restrict lhs,
						t_vec3 const *restrict rhs)
{
	dst->x = lhs->x - rhs->x;
	dst->y = lhs->y - rhs->y;
	dst->z = lhs->z - rhs->z;
}
