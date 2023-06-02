/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_normalize.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdubois <tdubois@student.42angouleme.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 16:38:08 by tdubois           #+#    #+#             */
/*   Updated: 2023/06/02 03:08:36 by tdubois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt/utils/geometry.h>

extern inline float	vec3_normalize(
						t_vec3 *src)
{
	float	norm; 

	if (src->x == 0.0f && src->y == 0.0f && src->z == 0.0f)
		return (0.0f);
	norm = vec3_norm(src);
	src->x /= norm;
	src->y /= norm;
	src->z /= norm;
	return (norm);
}
