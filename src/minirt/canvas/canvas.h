/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   canvas.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdubois <tdubois@student.42angouleme.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 01:36:02 by tdubois           #+#    #+#             */
/*   Updated: 2023/05/03 16:08:50 by tdubois          ###   ########.fr       */
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

typedef struct s_canvas
{
	mlx_image_t	*front;
	mlx_image_t	*back;
}	t_canvas;

//canvas_create
//canvas_swap

#endif//CANVAS_H
