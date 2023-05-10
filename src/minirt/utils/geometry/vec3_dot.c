/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_dot.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdubois <tdubois@student.42angouleme.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 17:11:27 by tdubois           #+#    #+#             */
/*   Updated: 2023/05/10 17:14:52 by tdubois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt/utils/geometry.h>

/**
 * Compute dot product of vectors u and v.
 * @param[in] u First vector
 * @param[in] v Second vector
 * @returns dot_product
 */
extern inline float	vec3_dot(
						t_vec3 const *u,
						t_vec3 const *v)
{
	return (0.0f
		+ u->x * v->x
		+ u->y * v->y
		+ u->z * v->z);
}
