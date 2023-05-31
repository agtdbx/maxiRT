/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_label_update_content.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdubois <tdubois@student.42angouleme.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 09:43:19 by tdubois           #+#    #+#             */
/*   Updated: 2023/05/31 13:52:08 by tdubois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt/menu/menu.h>

#include <MLX42/MLX42.h>
#include <libft/libft.h>
#include <stddef.h>

void	vec3_label_update_content(
			mlx_t *mlx,
			t_menu *menu,
			t_vec3_label *label)
{
	float_label_update_content(mlx, menu, &label->label_x);
	float_label_update_content(mlx, menu, &label->label_y);
	float_label_update_content(mlx, menu, &label->label_z);
}
