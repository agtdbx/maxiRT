/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_scale.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdubois <tdubois@student.42angouleme.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 15:57:11 by tdubois           #+#    #+#             */
/*   Updated: 2023/06/09 14:58:18 by tdubois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt/app/utils/geometry/geometry_bonus.h"

extern inline void	vec3_scale(
						t_vec3 *vec,
						float scaling_factor)
{
	vec->x *= scaling_factor;
	vec->y *= scaling_factor;
	vec->z *= scaling_factor;
}
