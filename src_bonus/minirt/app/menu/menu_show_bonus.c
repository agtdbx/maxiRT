/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_show.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdubois <tdubois@student.42angouleme.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 17:45:57 by tdubois           #+#    #+#             */
/*   Updated: 2023/07/17 17:29:27 by tdubois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt/app/menu/menu_bonus.h"

#include <stdbool.h>
#include <stddef.h>

void	menu_show(
			t_menu *menu)
{
	menu->is_visible = true;
	if (menu->background != NULL)
		menu->background->enabled = true;
	camera_label_show(menu);
	ambient_label_show(menu);
	if (menu->object_panel.is_enabled)
		object_panel_show(menu);
	if (menu->light_panel.is_enabled)
		light_panel_show(menu);
}
