/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawings.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdubois <tdubois@student.42angouleme.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 20:01:33 by tdubois           #+#    #+#             */
/*   Updated: 2023/07/07 15:19:55 by tdubois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DRAWINGS_H
# define DRAWINGS_H

# include <stdint.h>

# include "MLX42/MLX42.h"

void	img_fill(
			mlx_image_t *img,
			int32_t color);

void	img_draw_square(
			mlx_image_t *img,
			int32_t const coords[2],
			int32_t size,
			int32_t color);

void	img_draw_divider(
			mlx_image_t *img,
			uint32_t y,
			int32_t color);

#endif // DRAWINGS_H
