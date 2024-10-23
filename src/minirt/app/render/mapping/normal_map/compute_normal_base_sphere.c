/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compute_normal_base_sphere.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouba <aderouba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 16:42:03 by aderouba          #+#    #+#             */
/*   Updated: 2023/07/06 16:45:53 by aderouba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt/app/app.h"

#include "minirt/app/utils/geometry/geometry.h"

void	compute_normal_base_sphere(t_vec3 normal_base[3])
{
	normal_base[1] = (t_vec3){0.0f, 1.0f, 0.0f};
	vec3_cross(&normal_base[2], &normal_base[1], &normal_base[0]);
	vec3_normalize(&normal_base[0]);
}
