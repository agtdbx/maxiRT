/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   canvas.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdubois <tdubois@student.42angouleme.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 01:36:02 by tdubois           #+#    #+#             */
/*   Updated: 2023/05/16 14:38:30 by tdubois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CANVAS_H
# define CANVAS_H

//> CANVAS MODEL
//>
//> modelize where rendering happens
//> holds two mlx images:
//>  - one that is displayed
//>  - and one for background rendering across frames

# include <MLX42/MLX42.h>
# include <libft/libft.h>
# include <stdint.h>

typedef struct s_canvas
{
	mlx_image_t	*front;
	mlx_image_t	*back;

	int32_t	width;
	int32_t	width_div_2;

	int32_t	height;
	int32_t	height_div_2;
}	t_canvas;

t_error	canvas_init(
			mlx_t *mlx,
			t_canvas *canvas);
void	canvas_swap(
			t_canvas *canvas);

#endif//CANVAS_H
