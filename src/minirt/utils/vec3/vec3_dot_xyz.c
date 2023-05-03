/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_dot_xyz.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdubois <tdubois@student.42angouleme.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 13:04:55 by tdubois           #+#    #+#             */
/*   Updated: 2023/05/03 13:10:16 by tdubois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt/utils/geometry.h>

/**
 * Compute dot product of vectors (x, y, z) and vec.
 * @param[in] x Coordinate of first vector
 * @param[in] y Coordinate of first vector
 * @param[in] z Coordinate of first vector
 * @param[in] vec Second vector
 * @returns dot_product
 */
extern inline float	vec3_dot_xyz(
						float x,
						float y,
						float z,
						t_vec3 const *vec)
{
	return (x * vec->x + y * vec->y + z * vec->z);
}
