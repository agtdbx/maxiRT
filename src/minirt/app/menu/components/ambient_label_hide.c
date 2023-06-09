/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ambient_label_hide.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdubois <tdubois@student.42angouleme.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 09:03:12 by tdubois           #+#    #+#             */
/*   Updated: 2023/06/09 14:27:15 by tdubois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt/app/menu/menu.h"

#include <stdbool.h>

#include "minirt/app/utils/color/color.h"

void	ambient_label_hide(
			t_menu *menu)
{
	menu->ambient_label_title->enabled = false;
	color_label_hide(&menu->ambient_color_label);
	float_label_hide(&menu->ambient_ratio_label);
}
