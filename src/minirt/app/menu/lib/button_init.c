/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   button_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdubois <tdubois@student.42angouleme.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 16:37:33 by tdubois           #+#    #+#             */
/*   Updated: 2023/07/07 16:39:20 by tdubois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42/MLX42.h"
#include "minirt/app/menu/menu.h"
#include "minirt/app/utils/drawings/drawings.h"

void	button_init(
			mlx_t *mlx,
			t_button *button,
			int32_t	pos[2])
{
	button->x = pos[0];
	button->y = pos[1];
	button->img = mlx_new_image(mlx, 20 * 2, 20);
	if (button->img != NULL)
	{
		mlx_image_to_window(mlx, button->img, pos[0], pos[1]);
		img_fill(button->img, 0xFF0000FF);
		button->img->instances->enabled = false;
	}
	button->img_minus = mlx_put_string(mlx, "-", pos[0], pos[1]);
	if (button->img_minus != NULL)
		button->img_minus->instances->enabled = false;
	button->img_plus = mlx_put_string(mlx, "+", pos[0], pos[1]);
	if (button->img_plus != NULL)
		button->img_plus->instances->enabled = false;
}
