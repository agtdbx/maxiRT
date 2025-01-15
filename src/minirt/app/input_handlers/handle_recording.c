/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_recording.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dguillau <dguillau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 23:40:44 by damien            #+#    #+#             */
/*   Updated: 2025/01/15 11:45:02 by dguillau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt/app/encode/encode.h"
#include "minirt/app/menu/menu.h"

void	handle_recording(
				mlx_t *mlx,
				t_menu menu,
				mlx_image_t *record_icon,
				t_encode *encoder,
				t_error *err)
{
	static double	time_elapsed = 0;

	if (mlx_is_key_down(mlx, MLX_KEY_R) && menu.is_visible == false)
	{
		time_elapsed += mlx->delta_time;
		if (time_elapsed < 1)
			return ;
		encoder->is_recording ? close_recording(encoder, record_icon) :
			start_recording(record_icon, encoder, err, mlx);
		time_elapsed = 0;
		encoder->frame_counter = 0;
	}
	else
		time_elapsed = 0;
}
