/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compute_normal_base_paraboloid.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damien <damien@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 19:28:24 by damien            #+#    #+#             */
/*   Updated: 2025/01/16 19:29:59 by damien           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt/app/app.h"

#include "minirt/app/utils/geometry/geometry.h"

void	compute_normal_base_paraboloid(
				t_vec3 normal_base[3],
				t_paraboloid const *paraboloid)
{
	vec3_normalize(&normal_base[0]);
	vec3_scale(&normal_base[0], -1.0f);
	normal_base[1] = paraboloid->dir;
	vec3_scale(&normal_base[1], -1.0f);
}
