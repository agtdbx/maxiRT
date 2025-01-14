/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   img_draw_circle.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damien <damien@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 01:46:06 by damien            #+#    #+#             */
/*   Updated: 2025/01/10 01:46:36 by damien           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt/app/app_config.h"
#include "minirt/app/utils/drawings/drawings.h"

#include <math.h>

#define X 0
#define Y 1

void	img_draw_circle(mlx_image_t *img, const int32_t coords[2], int radius, int color)
{
	double	i, x, y;

	for (; radius > 0; radius--)
	{
		for (i = 0; i < 360; i += 0.1)
		{
			x = radius * cos(i * g_pi_div_180);
			y = radius * sin(i * g_pi_div_180);
			mlx_put_pixel(img, coords[X] + x, coords[Y] + y, color);
		}
	}
}
