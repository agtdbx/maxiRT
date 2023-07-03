/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere_panel_draw.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdubois <tdubois@student.42angouleme.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 12:16:20 by tdubois           #+#    #+#             */
/*   Updated: 2023/07/03 12:19:31 by tdubois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42/MLX42.h"
#include "minirt/app/menu/menu.h"

void	sphere_panel_draw(
			mlx_t *mlx,
			t_menu *menu)
{
	vec3_label_draw(mlx, menu, &menu->object_panel.sphere_label.position_label);
	float_label_draw(mlx, menu, &menu->object_panel.sphere_label.diameter_label);
}
