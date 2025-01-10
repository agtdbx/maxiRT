/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   encode.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damien <damien@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 23:17:02 by damien            #+#    #+#             */
/*   Updated: 2025/01/10 10:41:09 by damien           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENCODE_H
# define ENCODE_H

#include <stdio.h>
#include <libavcodec/avcodec.h>
#include <libavutil/imgutils.h>
#include <libswscale/swscale.h>

#include "MLX42/MLX42.h"
#include "libft/libft.h"

#include "minirt/app/scene/scene.h"

typedef struct s_encode
{
	FILE				*f;
	AVCodec				*codec;
	AVCodecContext		*c;
	AVFrame				*frame;
	AVPacket			*pkt;
	struct SwsContext	*sws_context;
	bool				is_recording;
	int					frame_counter;
}	t_encode;

void		create_records_dir();
t_error		encode_frame(mlx_image_t *img, t_encode *encoder);
void		close_recording(t_encode *encoder, mlx_image_t *record_icon);
void		start_recording(mlx_image_t *record_icon, t_encode *encoder, t_error *err);
t_error		init_encoder(t_encode *encoder, mlx_image_t *record_icon);
void		free_encoder_context(t_encode *encoder);
void		handle_recording(mlx_t *mlx, mlx_image_t *record_icon, t_encode *encoder, t_error *err);

#endif
