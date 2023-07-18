/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_label_init.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdubois <tdubois@student.42angouleme.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 15:47:13 by tdubois           #+#    #+#             */
/*   Updated: 2023/07/12 21:05:04 by tdubois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt/app/menu/menu.h"

#include "MLX42/MLX42.h"

#include <stdint.h>

static const uint32_t	g_pos[2] = {20, 10};

void	camera_label_init(
			mlx_t *mlx,
			t_menu *menu,
			t_scene const *scene)
{

	menu->camera_label_title = mlx_put_string(mlx, "camera:", g_pos[0], g_pos[1]);
	menu->camera_pos_label = vec3_label_init(mlx, menu, "position: ", 
		(uint32_t[2]){g_pos[0], g_pos[1] + 30});
	menu->camera_pos_label.label_x.f = &scene->camera->pos.x;
	menu->camera_pos_label.label_y.f = &scene->camera->pos.y;
	menu->camera_pos_label.label_z.f = &scene->camera->pos.z;
	menu->camera_dir_label = vec3_label_init(mlx, menu, "direction: ", 
		(uint32_t[2]){g_pos[0] + 180, g_pos[1] + 30});
	menu->camera_dir_label.label_x.f = &scene->camera->direction.x;
	menu->camera_dir_label.label_y.f = &scene->camera->direction.y;
	menu->camera_dir_label.label_z.f = &scene->camera->direction.z;
	float_label_init(&menu->camera_fov_label, "fov: ",
		(uint32_t[2]){g_pos[0], g_pos[1] + 120});
	menu->camera_fov_label.f = &scene->camera->fov;
	button_init(mlx, &menu->camera_fov_button,
		(int32_t[2]){g_pos[0] + 130, g_pos[1] + 120});
	menu->camera_fov_button.f = &scene->camera->fov;
	menu->camera_fov_button.min = 0.0f;
	menu->camera_fov_button.max = 180.0f;
	menu->camera_fov_button.step = 1.0f;
}
