/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   float_label_update_position.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdubois <tdubois@student.42angouleme.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 15:41:32 by tdubois           #+#    #+#             */
/*   Updated: 2023/05/31 16:14:09 by tdubois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt/menu/menu.h>

void	float_label_update_position(
			t_menu *menu,
			t_float_label *label)
{
	if (label->img == NULL)
		return ;
	label->img->instances->x = menu->background->instances->x + label->x;
	label->img->instances->y = menu->background->instances->y + label->y;
}
