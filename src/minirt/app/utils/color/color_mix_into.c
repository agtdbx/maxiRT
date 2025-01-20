/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_mix_into.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damien <damien@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 01:16:58 by damien            #+#    #+#             */
/*   Updated: 2025/01/19 10:09:51 by damien           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt/app/utils/color/color.h"
#include "minirt/app/utils/geometry/geometry.h"

void	mix_color_into(
			t_vec3 *res,
			t_vec3 *color_a,
			t_vec3 *color_b,
			float a)
{
	t_vec3	v, s;

	// x × (1 − a) + y × a.
	vec3_scale_into(&s, color_a, 1.0 - a);
	vec3_scale_into(&v, color_b, a);
	vec3_add_into(res, &s, &v);
}
