/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_label_update_position.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdubois <tdubois@student.42angouleme.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 15:40:11 by tdubois           #+#    #+#             */
/*   Updated: 2023/05/31 16:17:43 by tdubois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt/menu/menu.h>

void	vec3_label_update_position(
			t_menu *menu,
			t_vec3_label *label)
{
	float_label_update_position(menu, &label->label_x);
	float_label_update_position(menu, &label->label_y);
	float_label_update_position(menu, &label->label_z);
	if (label->img_title == NULL)
		return ;
	label->img_title->instances->x = menu->background->instances->x + label->x;
	label->img_title->instances->y = menu->background->instances->y + label->y;
}
