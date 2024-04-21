/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_add_into_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auguste <auguste@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 12:03:03 by tdubois           #+#    #+#             */
/*   Updated: 2024/04/21 12:37:44 by auguste          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt/app/utils/geometry/geometry_bonus.h"

/**
 * Stores result of lhs + rhs into dst.
 * @param[out] dst
 * @param[in] lhs
 * @param[in] rhs
 */
extern inline void	vec3_add_into(
						t_vec3 *restrict dst,
						t_vec3 const *restrict lhs,
						t_vec3 const *restrict rhs)
{
	dst->x = lhs->x + rhs->x;
	dst->y = lhs->y + rhs->y;
	dst->z = lhs->z + rhs->z;
}
