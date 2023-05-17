/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_menu_toggling.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdubois <tdubois@student.42angouleme.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 17:12:04 by tdubois           #+#    #+#             */
/*   Updated: 2023/05/17 17:37:56 by tdubois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt/app/app.h>

#include <minirt/menu/menu.h>
#include <MLX42/MLX42.h>
#include <stdbool.h>

bool	handle_menu_toggling(
			mlx_t *mlx,
			t_menu *menu)
{
	static bool		is_keypressed = false;

	if (!mlx_is_key_down(mlx, MLX_KEY_TAB))
	{
		if (is_keypressed)
			is_keypressed = false;
		return (false);
	}
	if (is_keypressed)
		return (false);
	is_keypressed = true;
	menu_toggle(menu);
	return (true);
}
