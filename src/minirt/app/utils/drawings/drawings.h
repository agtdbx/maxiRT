/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawings.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damien <damien@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 20:01:33 by tdubois           #+#    #+#             */
/*   Updated: 2025/01/10 00:30:26 by damien           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DRAWINGS_H
# define DRAWINGS_H

# include <stdint.h>
# include <pthread.h>

# include "MLX42/MLX42.h"
# include "minirt/app/render/multithread/multithread.h"

void	img_fill(
			mlx_image_t *img,
			int32_t color);

void	img_draw_square(
			t_sync *sync,
			pthread_mutex_t *img_mutex,
			mlx_image_t *img,
			int32_t const coords[2],
			int32_t size,
			int32_t color);

void	img_draw_divider(
			mlx_image_t *img,
			uint32_t y,
			int32_t color);

void	img_draw_circle(
			mlx_image_t *img,
			const int32_t coords[2],
			int radius,
			int color);

#endif // DRAWINGS_H
