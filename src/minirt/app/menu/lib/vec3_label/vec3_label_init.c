/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_label_init.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdubois <tdubois@student.42angouleme.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 10:29:27 by tdubois           #+#    #+#             */
/*   Updated: 2023/07/03 16:07:38 by tdubois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt/app/menu/menu.h"

#include <stdint.h>

t_vec3_label	vec3_label_init(
					mlx_t *mlx,
					t_menu *menu,
					char const *title,
					uint32_t const pos[2])
{
	t_vec3_label	label;

	label.title = title;
	label.x = pos[0];
	label.y = pos[1];
	label.img_title = mlx_put_string(
			mlx, label.title,
			menu->background->instances->x + pos[0], pos[1]);
	float_label_init(
		&label.label_x, "| x: ", (uint32_t[2]){pos[0], pos[1] + 20});
	float_label_init(
		&label.label_y, "| y: ", (uint32_t[2]){pos[0], pos[1] + 40});
	float_label_init(
		&label.label_z, "| z: ", (uint32_t[2]){pos[0], pos[1] + 60});
	return (label);
}
