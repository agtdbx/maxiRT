/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   img_fill.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdubois <tdubois@student.42angouleme.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 20:03:45 by tdubois           #+#    #+#             */
/*   Updated: 2023/05/31 20:04:38 by tdubois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt/utils/drawings.h>

void	img_fill(
			mlx_image_t *img,
			int32_t color)
{
	register uint32_t	x;
	register uint32_t	y;

	y = 0;
	while (y < img->height)
	{
		x = 0;
		while (x < img->width)
		{
			mlx_put_pixel(img, x, y, color);
			++x;
		}
		++y;
	}
}
