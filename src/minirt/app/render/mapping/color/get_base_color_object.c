/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_base_color_object.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damien <damien@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 12:52:20 by aderouba          #+#    #+#             */
/*   Updated: 2024/12/26 16:39:08 by damien           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt/app/app.h"

static t_color	apply_checkboard(
					t_vec2 const *pixel_pos);
static t_color	apply_sinusoide(
					t_vec2 const *pixel_pos);
static t_color	apply_perlin_noise(
					t_vec2 const *pixel_pos);

t_color	get_base_color_object(
			t_object const *intersected_object,
			t_vec2 const *pixel_pos)
{
	if (intersected_object->color_type == C_COLOR)
		return (intersected_object->color);
	else if (intersected_object->color_type == C_CHECKBOARD)
		return (apply_checkboard(pixel_pos));
	else if (intersected_object->color_type == C_SINUSOIDE)
		return (apply_sinusoide(pixel_pos));
	else if (intersected_object->color_type == C_PERLIN_NOISE)
		return (apply_perlin_noise(pixel_pos));
	else
	{
		return (apply_texture(intersected_object->texture, pixel_pos));
	}
}

static t_color	apply_checkboard(t_vec2 const *pixel_pos)
{
	t_color	res;

	res = (t_color){0};
	if (((int)(pixel_pos->x * checkboard_size)
			+ (int)(pixel_pos->y * checkboard_size)) % 2)
	{
		res.r = 255;
		res.g = 255;
		res.b = 255;
	}
	return (res);
}

static t_color	apply_sinusoide(t_vec2 const *pixel_pos)
{
	t_color	res;
	float	x;
	float	y;
	float	ratioX;
	float	ratioY;
	float	ratio;

	x = pixel_pos->x * sinusoide_size;
	y = pixel_pos->y * sinusoide_size;
	ratioX = (sin(x) + 1.0) / 2.0;
	ratioY = (cos(y) + 1.0) / 2.0;
	ratio = (ratioX + ratioY) / 2.0;
	res.r = 255.0 * ratio;
	res.g = 255.0 * ratio;
	res.b = 255.0 * ratio;
	res.a = 255;
	return (res);
}

static t_color	apply_perlin_noise(t_vec2 const *pixel_pos)
{
	t_color	res;
	int		x;
	int		y;

	x = pixel_pos->x * perlin_noise_size;
	y = pixel_pos->y * perlin_noise_size;
	res = (t_color){0};
	if ((x + y) % 2)
	{
		res.r = 255;
		res.g = 255;
		res.b = 255;
	}
	return (res);
}
