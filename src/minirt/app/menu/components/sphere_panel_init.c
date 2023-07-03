/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere_panel_init.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdubois <tdubois@student.42angouleme.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 11:10:59 by tdubois           #+#    #+#             */
/*   Updated: 2023/07/03 13:50:32 by tdubois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt/app/menu/menu.h"
#include <stdint.h>

void	sphere_panel_init(
			mlx_t *mlx,
			t_menu *menu)
{
	uint32_t const	pos[2] = {20, 440};

	menu->object_panel.sphere_label.position_label = 
		vec3_label_init(mlx, menu, "position: ", pos);
	float_label_init(&menu->object_panel.sphere_label.diameter_label,
		"diameter: ", (uint32_t[2]){pos[0] + 180, pos[1]});
}
