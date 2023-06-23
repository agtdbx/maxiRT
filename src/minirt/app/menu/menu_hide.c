/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_hide.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdubois <tdubois@student.42angouleme.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 17:42:34 by tdubois           #+#    #+#             */
/*   Updated: 2023/06/23 18:32:31 by tdubois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt/app/menu/menu.h"

#include <stdbool.h>
#include <stddef.h>

void	menu_hide(
			t_menu *menu)
{
	menu->is_visible = false;
	if (menu->background != NULL)
		menu->background->enabled = false;
	camera_label_hide(menu);
	ambient_label_hide(menu);
	object_panel_hide(menu);
}
