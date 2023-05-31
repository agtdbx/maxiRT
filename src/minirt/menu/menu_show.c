/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_show.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdubois <tdubois@student.42angouleme.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 17:45:57 by tdubois           #+#    #+#             */
/*   Updated: 2023/05/31 17:46:20 by tdubois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt/menu/menu.h>

void	menu_show(
			t_menu *menu)
{
	menu->is_visible = true;
	if (menu->background != NULL)
		menu->background->enabled = true;
	camera_label_show(menu);
}
