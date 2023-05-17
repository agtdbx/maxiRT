/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdubois <tdubois@student.42angouleme.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 15:54:53 by tdubois           #+#    #+#             */
/*   Updated: 2023/05/17 15:37:07 by tdubois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt/menu/menu.h>

#include <libft/libft.h>
#include <MLX42/MLX42.h>
#include <stdbool.h>

void	fill_img(
			mlx_image_t *img,
			int color)
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

t_error	menu_init(
			mlx_t *mlx,
			t_menu *menu)
{
	menu->is_visible = true;
	menu->background = mlx_new_image(mlx, MENU_WIDTH, mlx->height);
	if (menu->background == NULL)
		return (FAILURE);
	fill_img(menu->background, MENU_BACKGROUND_COLOR);
	// menu->background->enabled = false;
	if (mlx_image_to_window(mlx, menu->background, 0, 0) == -1)
		return (FAILURE);
	mlx_set_instance_depth(&menu->background->instances[0], 2);
	menu_update_position(mlx, menu);
	return (SUCCESS);
}
