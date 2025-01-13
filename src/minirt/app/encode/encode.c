/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   encode.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damien <damien@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 23:16:49 by damien            #+#    #+#             */
/*   Updated: 2025/01/10 15:50:32 by damien           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt/app/app.h"

#include <sys/types.h>
#include <sys/stat.h>

#include <libavcodec/avcodec.h>
#include <libswscale/swscale.h>

#include "MLX42/MLX42.h"
#include "libft/libft.h"

#include "minirt/app/app_config.h"
#include "minirt/app/scene/scene.h"
#include "minirt/app/encode/encode.h"
#include "minirt/app/utils/drawings/drawings.h"

#define MAX_FILENAME_SIZE 256

static void set_path_record_file(char *filename)
{
	time_t		timestamp;
	struct tm	*date;

	timestamp = time(NULL);
	date = localtime(&timestamp);
	strftime(filename, MAX_FILENAME_SIZE,
		"records/record_%d_%m_%Y+%H:%M:%S.avi", date);
}

void	start_recording(mlx_image_t *record_icon, t_encode *encoder, t_error *err)
{
	char	filename[MAX_FILENAME_SIZE] = {0};

	set_path_record_file(filename);
	encoder->f = fopen(filename, "wb");
	if (!encoder->f)
	{
		fprintf(stderr, "Could not open %s\n", filename);
		*err = FAILURE;
	}
	mlx_set_instance_depth(&record_icon->instances[0], 2);
	encoder->is_recording = true;
}

void	free_encoder_context(t_encode *encoder)
{
	if (encoder->is_recording)
		fclose(encoder->f);
	if (encoder->sws_context)
		sws_freeContext(encoder->sws_context);
	if (encoder->c)
		avcodec_free_context(&encoder->c);
	if (encoder->frame)
		av_frame_free(&encoder->frame);
	if (encoder->pkt)
		av_packet_free(&encoder->pkt);
}

/**
 * @brief Implemented from https://www.ffmpeg.org/doxygen/4.0/encode_video_8c-example.html
 * 
 * @param enc_ctx 
 * @param frame 
 * @param pkt 
 * @param outfile 
 * @return t_error 
 */

static t_error	encode(AVCodecContext *enc_ctx, AVFrame *frame, AVPacket *pkt,
		FILE *outfile)
{
	int	ret = 0;

	ret = avcodec_send_frame(enc_ctx, frame);
	if (ret < 0)
	{
		fprintf(stderr, "Error sending a frame for encoding\n");
		return FAILURE;
	}
	while (ret >= 0)
	{
		ret = avcodec_receive_packet(enc_ctx, pkt);
		if (ret == AVERROR(EAGAIN) || ret == AVERROR_EOF)
			return SUCCESS;
		fwrite(pkt->data, 1, pkt->size, outfile);
		av_packet_unref(pkt);
	}
	return SUCCESS;
}

void	close_recording(t_encode *encoder, mlx_image_t *record_icon)
{
	static uint8_t	endcode[] = { 0, 0, 1, 0xb7 };

	mlx_set_instance_depth(&record_icon->instances[0], 0);
	encode(encoder->c, NULL, encoder->pkt, encoder->f);
	fwrite(endcode, 1, sizeof(endcode), encoder->f);
	free_encoder_context(encoder);
	init_encoder(encoder, record_icon);
}

t_error	init_encoder(t_encode *encoder, mlx_image_t *record_icon)
{
	const AVCodec			*codec;
	int						ret;
	static const int32_t	coords[2] = {20, 990};

	img_draw_circle(record_icon, coords, 10, 0xFF0000FF);
	encoder->is_recording = false;
	encoder->frame_counter = 0;
	codec = avcodec_find_encoder(AV_CODEC_ID_MPEG1VIDEO);
	if (!codec)
	{
		fprintf(stderr, "codec not found\n");
		exit(1);
	}
	encoder->c = avcodec_alloc_context3(codec);
	if (!encoder->c)
	{
		fprintf(stderr, "could not allocate video codec context\n");
		return FAILURE;
	}
	encoder->pkt = av_packet_alloc();
	if (!encoder->pkt)
		return FAILURE;
	encoder->c->bit_rate = 400000;
	encoder->c->width = 1920;
	encoder->c->height = 1011;
	encoder->c->time_base= (AVRational){1,25};
	encoder->c->framerate = (AVRational){25, 1};
	encoder->c->gop_size = 10;
	encoder->c->max_b_frames=1;
	encoder->c->pix_fmt = AV_PIX_FMT_YUV420P;
	ret = avcodec_open2(encoder->c, codec, NULL);
	if (ret < 0)
	{
		fprintf(stderr, "Could not open codec: %s\n", av_err2str(ret));
		return FAILURE;
	}
	encoder->frame = av_frame_alloc();
	if (!encoder->frame)
	{
		fprintf(stderr, "Could not allocate video frame\n");
		return FAILURE;
	}
	encoder->frame->format = encoder->c->pix_fmt;
	encoder->frame->width  = encoder->c->width;
	encoder->frame->height = encoder->c->height;
	ret = av_frame_get_buffer(encoder->frame, 32);
	if (ret < 0)
	{
		fprintf(stderr, "Could not allocate the video frame data\n");
		return FAILURE;
	}
	encoder->sws_context = sws_getContext(
		1920,
		1011,
		AV_PIX_FMT_RGBA,
		encoder->c->width,
		encoder->c->height,
		AV_PIX_FMT_YUV420P,
		0, 0, 0, 0);
	return SUCCESS;
}

t_error	encode_frame(mlx_image_t *img, t_encode *encoder)
{
	int			ret;
	const int	src_stride[1] = { img->width * sizeof(int32_t) };

	ret = av_frame_make_writable(encoder->frame);
	if (ret < 0)
	{
		fprintf(stderr, "Error making frame writable\n");
		return FAILURE;
	}
	fflush(stdout);
	sws_scale(encoder->sws_context, (const uint8_t * const *)&img->pixels,
		src_stride, 0, 1011,
			encoder->frame->data, encoder->frame->linesize);
	encoder->frame->pts = encoder->frame_counter++;
	return encode(encoder->c, encoder->frame, encoder->pkt, encoder->f);
}


void	create_records_dir()
{
	struct stat	st;

	if (stat("/records/", &st) == -1)
		mkdir("records", 0777);
}
