/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rgb_to_luma.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dguillau <dguillau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 20:16:51 by damien            #+#    #+#             */
/*   Updated: 2025/01/20 11:59:06 by dguillau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt/app/utils/color/color.h"
#include "minirt/app/utils/geometry/geometry.h"

float	rgb_to_luma(
			t_vec3 rgb)
{
	return vec3_dot_xyz(0.2126, 0.7152, 0.0722, &rgb);
}
