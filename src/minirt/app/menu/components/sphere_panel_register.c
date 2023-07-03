/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere_panel_register.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdubois <tdubois@student.42angouleme.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 11:57:08 by tdubois           #+#    #+#             */
/*   Updated: 2023/07/03 12:00:48 by tdubois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt/app/menu/menu.h"

#include "minirt/app/scene/scene.h"

void	sphere_panel_register(
			t_menu *menu,
			t_sphere *sphere)
{
	menu->object_panel.sphere_label.position_label.label_x.f = &sphere->pos.x;
	menu->object_panel.sphere_label.position_label.label_y.f = &sphere->pos.y;
	menu->object_panel.sphere_label.position_label.label_z.f = &sphere->pos.z;
	menu->object_panel.sphere_label.diameter_label.f = &sphere->diameter;
}
