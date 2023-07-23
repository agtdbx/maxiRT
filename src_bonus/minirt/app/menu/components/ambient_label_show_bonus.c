/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ambient_label_show.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdubois <tdubois@student.42angouleme.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 09:01:31 by tdubois           #+#    #+#             */
/*   Updated: 2023/07/12 20:55:03 by tdubois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt/app/menu/menu_bonus.h"

#include <stdbool.h>

#include "minirt/app/utils/color/color_bonus.h"

void	ambient_label_show(
			t_menu *menu)
{
	menu->ambient_label_title->enabled = true;
	color_label_show(&menu->ambient_color_label);
	float_label_show(&menu->ambient_ratio_label);
	button_show(&menu->ambient_ratio_button);
	button_show(&menu->ambient_color_button_r);
	button_show(&menu->ambient_color_button_g);
	button_show(&menu->ambient_color_button_b);
}
