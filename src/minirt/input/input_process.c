/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdubois <tdubois@student.42angouleme.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 00:48:42 by tdubois           #+#    #+#             */
/*   Updated: 2023/04/14 01:51:14 by tdubois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt/app/app.h>
#include <minirt/input/input.h>
#include <MLX42/MLX42.h>
#include <stddef.h>

//---- DECLARATIONS ----------------------------------------------------------//

void				input_process(t_app *const app);
static inline void		_process_keyboard_inputs(t_app *const app);
static inline void		_process_mouse_inputs(t_app *const app);

//---- DEFINITIONS -----------------------------------------------------------//

void	input_process(t_app *const app)
{
	_process_keyboard_inputs(app);
	_process_mouse_inputs(app);
}

static inline void	_process_keyboard_inputs(t_app *const app)
{
	register size_t	i;

	i = 0;
	while (i < sizeof(g_keyhooks) / sizeof(t_hook))
	{
		if (mlx_is_key_down(app->mlx, g_keyhooks[i].code))
			g_keyhooks[i].callback(app);
		i++;
	}
}

static inline void	_process_mouse_inputs(t_app *const app)
{
	register size_t	i;

	i = 0;
	while (i < sizeof(g_mousehooks) / sizeof(t_hook))
	{
		if (mlx_is_mouse_down(app->mlx, g_mousehooks[i].code))
			g_mousehooks[i].callback(app);
		i++;
	}
}
