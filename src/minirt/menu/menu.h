/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdubois <tdubois@student.42angouleme.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 01:39:57 by tdubois           #+#    #+#             */
/*   Updated: 2023/05/22 08:53:12 by tdubois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MENU_H
# define MENU_H

//> MENU MODEL

# include <libft/libft.h>
# include <MLX42/MLX42.h>
# include <stdbool.h>

# define MENU_WIDTH 400 // width of menu in pixels
# define MENU_BACKGROUND_COLOR 0x333333FF

typedef struct s_menu
{
	bool		is_visible;

	mlx_image_t	*background;
}	t_menu;

t_error	menu_init(
			mlx_t *mlx,
			t_menu *menu);
void	menu_update_position(
			mlx_t const *mlx,
			t_menu *menu);
void	menu_toggle(
			t_menu *menu);

#endif//MENU_H
