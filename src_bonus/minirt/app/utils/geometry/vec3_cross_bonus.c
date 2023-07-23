/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_cross.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouba <aderouba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 17:26:23 by aderouba          #+#    #+#             */
/*   Updated: 2023/06/21 17:27:47 by aderouba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt/app/utils/geometry/geometry_bonus.h"

extern inline void	vec3_cross(
						t_vec3 const *v1,
						t_vec3 const *v2,
						t_vec3 *vec_res)
{
	vec_res->x = (v1->y * v2->z) - (v1->z * v2->y);
	vec_res->y = (v1->z * v2->x) - (v1->x * v2->z);
	vec_res->z = (v1->x * v2->y) - (v1->y * v2->x);
}
