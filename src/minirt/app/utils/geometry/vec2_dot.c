/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec2_dot.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gugus <gugus@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 17:11:27 by tdubois           #+#    #+#             */
/*   Updated: 2025/01/16 03:07:00 by gugus            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt/app/utils/geometry/geometry.h"

/**
 * Compute dot product of vectors u and v.
 * @param[in] u First vector
 * @param[in] v Second vector
 * @returns dot_product
 */
extern inline float	vec2_dot(
						t_vec2 const *u,
						t_vec2 const *v)
{
	return (u->x * v->x + u->y * v->y);
}
