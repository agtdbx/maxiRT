/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   button_draw.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdubois <tdubois@student.42angouleme.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 17:01:49 by tdubois           #+#    #+#             */
/*   Updated: 2023/07/17 10:41:47 by tdubois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42/MLX42.h"
#include "MLX42/MLX42_Input.h"
#include "minirt/app/menu/menu.h"
#include "minirt/app/utils/drawings/drawings.h"

#include <stdbool.h>
#include <stdio.h>
#include <math.h>

static bool	_draw_left_button(
				int32_t const pos_click[2],
				t_button *button);

static bool	_draw_right_button(
				int32_t const pos_click[2],
				t_button *button);

bool	button_draw(
			mlx_t *mlx,
			t_menu *menu,
			t_button *button)
{
	int32_t	pos_click[2];
	bool	should_render;

	button->img->instances[0].x = menu->background->instances[0].x + button->x;
	button->img_minus->instances[0].x = menu->background->instances[0].x + button->x + 5;
	button->img_plus->instances[0].x = menu->background->instances[0].x + button->x + 25;
	if (!mlx_is_mouse_down(mlx, MLX_MOUSE_BUTTON_LEFT))
	{
		img_fill(button->img, 0xFF0000FF);
		return (false);
	}
	mlx_get_mouse_pos(mlx, &pos_click[0], &pos_click[1]);
	if (pos_click[0] < menu->background->instances[0].x
		|| !(button->y <= pos_click[1] && pos_click[1] < button->y + 20))
		return (false);
	pos_click[0] -= menu->background->instances[0].x;
	should_render = false;
	should_render |= _draw_left_button(pos_click, button);
	should_render |= _draw_right_button(pos_click, button);
	return (should_render);
}

static bool	_draw_left_button(
				int32_t const pos_click[2],
				t_button *button)
{
	int32_t	const pos_button[2] = { button->x, button->y };
	int32_t const pos_inside_img[2] = {0,0};

	if (pos_button[0] <= pos_click[0] && pos_click[0] < pos_button[0] + 20)
	{
		img_draw_square(button->img, pos_inside_img, 20, 0x00FF00FF);
		if (button->min < *button->f)
		{
			*button->f = fmaxf(button->min, *button->f - button->step) ;
			return (true);
		}
		return (false);
	}
	img_draw_square(button->img, pos_inside_img, 20, 0xFF0000FF);
	return (false);
}

static bool	_draw_right_button(
				int32_t const pos_click[2],
				t_button *button)
{
	int32_t	const pos_button[2] = { button->x + 20, button->y };
	int32_t const pos_inside_img[2] = {20,0};

	if (pos_button[0] <= pos_click[0] && pos_click[0] < pos_button[0] + 20)
	{
		img_draw_square(button->img, pos_inside_img, 20, 0x00FF00FF);
		if (*button->f < button->max)
		{
			*button->f = fminf(button->max, *button->f + button->step) ;
			return (true);
		}
		return (false);
	}
	img_draw_square(button->img, pos_inside_img, 20, 0xFF0000FF);
	return (false);
}
