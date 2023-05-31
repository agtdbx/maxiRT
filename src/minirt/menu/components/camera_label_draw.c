/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_label_draw.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdubois <tdubois@student.42angouleme.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 17:51:24 by tdubois           #+#    #+#             */
/*   Updated: 2023/05/31 17:53:56 by tdubois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt/menu/menu.h>

void	camera_label_draw(
			mlx_t *mlx,
			t_menu *menu)
{
	vec3_label_update_position(menu, &menu->camera_dir_label);
	vec3_label_update_content(mlx, menu, &menu->camera_dir_label);
	vec3_label_update_position(menu, &menu->camera_pos_label);
	vec3_label_update_content(mlx, menu, &menu->camera_pos_label);
}
