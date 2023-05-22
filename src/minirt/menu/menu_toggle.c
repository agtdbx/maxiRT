/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_toggle.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdubois <tdubois@student.42angouleme.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 08:50:16 by tdubois           #+#    #+#             */
/*   Updated: 2023/05/22 08:52:59 by tdubois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt/menu/menu.h>

void	menu_toggle(
			t_menu *menu)
{
	menu->is_visible = !menu->is_visible;
	menu->background->instances->enabled = menu->is_visible;
}
