/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rgb_to_luma.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damien <damien@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 20:16:51 by damien            #+#    #+#             */
/*   Updated: 2025/01/18 20:17:08 by damien           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt/app/utils/color/color.h"

float	rgb_to_luma(
			t_vec3 rgb)
{
	t_vec3 norm;

	vec3_normalize_into(&norm, &rgb);
	return vec3_dot(&norm, &(t_vec3) {0.2126, 0.7152, 0.0722});
}
