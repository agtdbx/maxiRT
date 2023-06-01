/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ambient_label_hide.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdubois <tdubois@student.42angouleme.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 09:03:12 by tdubois           #+#    #+#             */
/*   Updated: 2023/06/01 10:14:07 by tdubois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt/menu/menu.h>

void	ambient_label_hide(
			t_menu *menu)
{
	menu->ambient_label_title->enabled = false;
	color_label_hide(&menu->ambient_color_label);
	float_label_hide(&menu->ambient_ratio_label);
}
