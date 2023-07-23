/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_scale_into.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouba <aderouba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 15:57:11 by tdubois           #+#    #+#             */
/*   Updated: 2023/07/05 18:28:29 by aderouba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt/app/utils/geometry/geometry_bonus.h"

extern inline void	vec3_scale_into(
						t_vec3 *res,
						t_vec3 const *restrict vec,
						float scaling_factor)
{
	res->x = vec->x * scaling_factor;
	res->y = vec->y * scaling_factor;
	res->z = vec->z * scaling_factor;
}
