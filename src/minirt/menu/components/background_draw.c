/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   background_draw.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdubois <tdubois@student.42angouleme.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 23:34:02 by tdubois           #+#    #+#             */
/*   Updated: 2023/06/01 10:24:46 by tdubois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt/menu/menu.h>

#include <minirt/utils/drawings.h>

void	background_draw(
			t_menu *menu)
{
	img_fill(menu->background, MENU_BACKGROUND_COLOR);
	img_draw_divider(
		menu->background, MENU_DIVIDER_1_Y, MENU_DIVIDERS_COLOR);
	img_draw_divider(
		menu->background, MENU_DIVIDER_2_Y, MENU_DIVIDERS_COLOR);
}
