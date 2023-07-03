/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_panel_hide.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdubois <tdubois@student.42angouleme.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 15:49:54 by tdubois           #+#    #+#             */
/*   Updated: 2023/07/03 12:15:14 by tdubois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt/app/menu/menu.h"

#include <stdbool.h>

#include "minirt/app/utils/color/color.h"

void	object_panel_hide(
			t_menu *menu)
{
	if (menu->object_panel.sphere_title != NULL)
		menu->object_panel.sphere_title->enabled = false;
	color_label_hide(&menu->object_panel.color_label);
	float_label_hide(&menu->object_panel.opacity_label);
	float_label_hide(&menu->object_panel.density_label);
	float_label_hide(&menu->object_panel.reflection_label);
	sphere_panel_hide(menu);
}
