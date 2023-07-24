/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   background_draw.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdubois <tdubois@student.42angouleme.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 23:34:02 by tdubois           #+#    #+#             */
/*   Updated: 2023/06/09 14:28:53 by tdubois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt/app/menu/menu_bonus.h"

#include "minirt/app/app_config_bonus.h"
#include "minirt/app/utils/drawings/drawings_bonus.h"

void	background_draw(
			t_menu *menu)
{
	img_fill(menu->background, g_menu_background_color);
	img_draw_divider(
		menu->background, g_menu_divider_1_y, g_menu_dividers_color);
	img_draw_divider(
		menu->background, g_menu_divider_2_y, g_menu_dividers_color);
}
