/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_linear_transform.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdubois <tdubois@student.42angouleme.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 16:36:45 by tdubois           #+#    #+#             */
/*   Updated: 2023/05/04 16:39:55 by tdubois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt/utils/geometry.h>

extern inline void	vec3_linear_transform(
						t_vec3 *restrict vec1,
						float scaling_factor,
						t_vec3 const *restrict vec2)
{
	vec1->x += scaling_factor * vec2->x;
	vec1->y += scaling_factor * vec2->y;
	vec1->z += scaling_factor * vec2->z;
}
