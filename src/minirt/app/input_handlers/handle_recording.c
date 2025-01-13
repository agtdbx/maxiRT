/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_recording.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damien <damien@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 23:40:44 by damien            #+#    #+#             */
/*   Updated: 2025/01/10 11:00:48 by damien           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt/app/encode/encode.h"

void	handle_recording(mlx_t *mlx, mlx_image_t *record_icon, t_encode *encoder, t_error *err)
{
	static double	time_elapsed = 0;

	if (mlx_is_key_down(mlx, MLX_KEY_R))
	{
		time_elapsed += mlx->delta_time;
		if (time_elapsed < 1)
			return ;
		encoder->is_recording ? close_recording(encoder, record_icon, mlx->width, mlx->height) :
			start_recording(record_icon, encoder, err);
		time_elapsed = 0;
		encoder->frame_counter = 0;
		
	}
	else
		time_elapsed = 0;
}
