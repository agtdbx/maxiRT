/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec2_label_init.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gugus <gugus@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 19:54:17 by gugus             #+#    #+#             */
/*   Updated: 2025/01/18 19:56:11 by gugus            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt/app/menu/menu.h"

#include <stdint.h>

t_vec2_label	vec2_label_init(
					mlx_t *mlx,
					t_menu *menu,
					char const *title,
					uint32_t const pos[2])
{
	t_vec2_label	label;

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
	return (label);
}
