/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdubois <tdubois@student.42angouleme.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 00:38:20 by tdubois           #+#    #+#             */
/*   Updated: 2023/04/14 01:49:51 by tdubois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INPUT_H
# define INPUT_H

# include <minirt/app/app.h>
# include <MLX42/MLX42.h>

//**** DECLARATIONS **********************************************************//

typedef struct s_hook
{
	int		code;
	void	(*callback)(t_app *const app);
}	t_hook;

static const t_hook	g_keyhooks[] = {
	// {MLX_KEY_TAB, toggle_menu}
	//
	// {MLX_KEY_W, move_forward},
	// {MLX_KEY_Z, move_forward},
	// {MLX_KEY_S, move_backward},
	// {MLX_KEY_A, move_left},
	// {MLX_KEY_Q, move_left},
	// {MLX_KEY_D, move_right},
	// {MLX_KEY_SPACE, move_upward},
	// {MLX_KEY_LEFT_SHIFT, move_downward},
	//
	// {MLX_KEY_UP, rotate_up},
	// {MLX_KEY_DOWN, rotate_down},
	// {MLX_KEY_LEFT, rotate_left},
	// {MLX_KEY_RIGHT, rotate_right},
};

static const t_hook	g_mousehooks[] = {
	// {MLX_MOUSE_BUTTON_LEFT, menu_click}
};

void	input_process(t_app *const app);

#endif//INPUT_H
