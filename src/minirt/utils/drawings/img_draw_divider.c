/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   img_draw_hline.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdubois <tdubois@student.42angouleme.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 23:16:52 by tdubois           #+#    #+#             */
/*   Updated: 2023/05/31 23:29:28 by tdubois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt/utils/drawings.h>

#include <MLX42/MLX42.h>

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
