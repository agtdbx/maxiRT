/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   img_draw_square.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdubois <tdubois@student.42angouleme.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 20:45:10 by tdubois           #+#    #+#             */
/*   Updated: 2023/07/07 15:36:35 by tdubois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt/app/utils/drawings/drawings_bonus.h"

#include <stdint.h>

#include "MLX42/MLX42.h"
#include "libft/libft.h"

#define X 0
#define Y 1

void	img_draw_square(
			mlx_image_t *img,
			int32_t const coords[2],
			int32_t size,
			int32_t color)
{
	int const		max_x = ft_min(coords[X] + size, img->width);
	int const		max_y = ft_min(coords[Y] + size, img->height);
	register int	x;
	register int	y;

	y = coords[Y];
	while (y < max_y)
	{
		x = coords[X];
		while (x < max_x)
		{
			mlx_put_pixel(img, x, y, color);
			++x;
		}
		++y;
	}
}
