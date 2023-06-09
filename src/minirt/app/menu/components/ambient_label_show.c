/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ambient_label_show.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdubois <tdubois@student.42angouleme.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 09:01:31 by tdubois           #+#    #+#             */
/*   Updated: 2023/06/09 14:26:20 by tdubois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt/app/menu/menu.h"

#include <stdbool.h>

#include "minirt/app/utils/color/color.h"

void	ambient_label_show(
			t_menu *menu)
{
	menu->ambient_label_title->enabled = true;
	color_label_show(&menu->ambient_color_label);
	float_label_show(&menu->ambient_ratio_label);
}
