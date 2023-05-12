/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_norm.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdubois <tdubois@student.42angouleme.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 16:10:21 by tdubois           #+#    #+#             */
/*   Updated: 2023/05/12 17:36:19 by tdubois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt/utils/geometry.h>

#include <math.h>

extern inline float	vec3_norm(
						t_vec3 const *vec)
{
	return (sqrtf(
			vec->x * vec->x
			+ vec->y * vec->y
			+ vec->z * vec->z));
}
