/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paraboloid_compute_constants.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damien <damien@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 15:47:55 by damien            #+#    #+#             */
/*   Updated: 2025/01/16 15:49:57 by damien           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt/app/scene/scene.h"

#include "minirt/app/utils/geometry/geometry.h"

#include "minirt/app/scene/scene.h"

void	paraboloid_compute_constants(
			t_paraboloid *paraboloid)
{
	vec3_normalize(&paraboloid->dir);
	paraboloid->k_mult_2 = paraboloid->k * 2.0f;
	paraboloid->k_mult_4 = paraboloid->k * 4.0f;
}
