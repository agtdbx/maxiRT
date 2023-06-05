/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_scale.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdubois <tdubois@student.42angouleme.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 14:47:51 by tdubois           #+#    #+#             */
/*   Updated: 2023/06/05 14:50:12 by tdubois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt/utils/color.h>

void	color_scale(
			t_color *color,
			float scaling_factor)
{
	color->r *= scaling_factor;
	color->g *= scaling_factor;
	color->b *= scaling_factor;
}
