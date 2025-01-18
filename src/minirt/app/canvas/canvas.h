/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   canvas.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damien <damien@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 01:36:02 by tdubois           #+#    #+#             */
/*   Updated: 2025/01/18 09:52:59 by damien           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CANVAS_H
# define CANVAS_H

# include <stdint.h>

# include "MLX42/MLX42.h"
# include "libft/libft.h"

typedef struct s_canvas
{
	mlx_image_t	*front;
	mlx_image_t	*back;
	mlx_image_t	*record_icon;
	mlx_image_t	*scaled_img;

	int32_t		width;
	int32_t		width_div_2;

	int32_t		height;
	int32_t		height_div_2;
}	t_canvas;

t_error	canvas_init(
			mlx_t *mlx,
			t_canvas *canvas);
void	canvas_swap(
			t_canvas *canvas);

#endif//CANVAS_H
