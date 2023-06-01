/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ambient_label_show.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdubois <tdubois@student.42angouleme.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 09:01:31 by tdubois           #+#    #+#             */
/*   Updated: 2023/06/01 10:14:36 by tdubois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt/menu/menu.h>

void	ambient_label_show(
			t_menu *menu)
{
	menu->ambient_label_title->enabled = true;
	color_label_show(&menu->ambient_color_label);
	float_label_show(&menu->ambient_ratio_label);
}
