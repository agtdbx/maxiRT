/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compute_normal_base_triangle_bonus.c               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auguste <auguste@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 16:42:22 by aderouba          #+#    #+#             */
/*   Updated: 2024/03/11 17:22:11 by auguste          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt/app/app_bonus.h"

#include "minirt/app/utils/geometry/geometry_bonus.h"

void	compute_normal_base_triangle(t_vec3 normal_base[3])
{
	if (normal_base[2].x != 0.0f || normal_base[2].y != 0.0f)
		normal_base[1] = (t_vec3){normal_base[2].y, -normal_base[2].x, 0.0f};
	else
		normal_base[1] = (t_vec3){0.0f, -1.0f, 0.0f};
	vec3_cross(&normal_base[2], &normal_base[1], &normal_base[0]);
	vec3_normalize(&normal_base[0]);
	vec3_normalize(&normal_base[1]);
}
