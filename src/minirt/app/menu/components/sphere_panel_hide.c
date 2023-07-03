/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere_panel_hide.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdubois <tdubois@student.42angouleme.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 12:01:14 by tdubois           #+#    #+#             */
/*   Updated: 2023/07/03 12:05:05 by tdubois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt/app/menu/menu.h"

void	sphere_panel_hide(
			t_menu *menu)
{
	vec3_label_hide(&menu->object_panel.sphere_label.position_label);
	float_label_hide(&menu->object_panel.sphere_label.diameter_label);
}
