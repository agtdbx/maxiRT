/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   img_draw_divider.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdubois <tdubois@student.42angouleme.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 23:16:52 by tdubois           #+#    #+#             */
/*   Updated: 2023/06/09 14:51:33 by tdubois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt/app/utils/drawings/drawings_bonus.h"

#include <stdint.h>

#include "MLX42/MLX42.h"

void	img_draw_divider(
			mlx_image_t *img,
			uint32_t y,
			int32_t color)
{
	register uint32_t	x;

	if (y >= img->height)
		return ;
	x = 0;
	while (x < img->width)
	{
		mlx_put_pixel(img, x, y, color);
		++x;
	}
}
