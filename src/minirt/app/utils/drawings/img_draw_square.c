/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   img_draw_square.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damien <damien@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 20:45:10 by tdubois           #+#    #+#             */
/*   Updated: 2024/12/26 15:33:55 by damien           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt/app/utils/drawings/drawings.h"

#include <pthread.h>
#include <stdint.h>

#include "MLX42/MLX42.h"
#include "libft/libft.h"

#define X 0
#define Y 1

void	img_draw_square(
			t_sync *sync,
			pthread_mutex_t *img_mutex,
			mlx_image_t *img,
			int32_t const coords[2],
			int32_t size,
			int32_t color)
{
	int const		max_x = ft_min(coords[X] + size, img->width);
	int const		max_y = ft_min(coords[Y] + size, img->height);
	register int	x;
	register int	y;

	if (img_mutex)
		pthread_mutex_lock(img_mutex);
	if (sync && sync->reset_render)
	{
		pthread_mutex_unlock(img_mutex);
		return ;
	}
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
	if (img_mutex)
		pthread_mutex_unlock(img_mutex);
}
