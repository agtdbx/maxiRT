/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   button_init_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouba <aderouba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 16:37:33 by tdubois           #+#    #+#             */
/*   Updated: 2023/07/23 15:17:50 by aderouba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42/MLX42.h"
#include "minirt/app/menu/menu_bonus.h"
#include "minirt/app/utils/drawings/drawings_bonus.h"

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
		img_fill(button->img, 0x333333FF);
		button->img->instances->enabled = false;
	}
	button->img_minus = mlx_put_string(mlx, "-", pos[0], pos[1]);
	if (button->img_minus != NULL)
		button->img_minus->instances->enabled = false;
	button->img_plus = mlx_put_string(mlx, "+", pos[0], pos[1]);
	if (button->img_plus != NULL)
		button->img_plus->instances->enabled = false;
}
