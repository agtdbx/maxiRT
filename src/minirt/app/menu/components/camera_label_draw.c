/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_label_draw.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdubois <tdubois@student.42angouleme.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 17:51:24 by tdubois           #+#    #+#             */
/*   Updated: 2023/07/03 16:01:23 by tdubois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt/app/menu/menu.h"

#include "MLX42/MLX42.h"

#include "minirt/app/utils/geometry/geometry.h"

void	camera_label_draw(
			mlx_t *mlx,
			t_menu *menu)
{
	menu->camera_label_title->instances->x = \
		menu->background->instances->x + 20;
	vec3_label_draw(mlx, menu, &menu->camera_dir_label);
	vec3_label_draw(mlx, menu, &menu->camera_pos_label);
	float_label_draw(mlx, menu, &menu->camera_fov_label);
}
