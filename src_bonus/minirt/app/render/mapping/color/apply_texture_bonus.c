/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_texture.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouba <aderouba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 16:08:47 by aderouba          #+#    #+#             */
/*   Updated: 2023/07/05 20:49:48 by aderouba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt/app/app_bonus.h"

static t_color	apply_texture_not_found(t_vec2 const *pixel_pos);
static t_vec2	compute_ratio_pos_pixel(
					mlx_texture_t const *texture,
					t_vec2 const *pixel_pos,
					int x[2],
					int y[2]);
static t_color	get_pixel_color(
					mlx_texture_t const *texture,
					int x,
					int y,
					int space_between_color);
static t_color	merge_color_with_ratio(
					t_vec2 const *ratio,
					t_color color[4]);

t_color	apply_texture(
					mlx_texture_t const *texture,
					t_vec2 const *pixel_pos)
{
	t_vec2		ratio;
	t_color		colors[4];
	int			x[2];
	int			y[2];
	int			space_between_color;

	if (!texture)
		return (apply_texture_not_found(pixel_pos));
	space_between_color = texture->bytes_per_pixel / 3;
	ratio = compute_ratio_pos_pixel(texture, pixel_pos, x, y);
	colors[0] = get_pixel_color(texture, x[0], y[0], space_between_color);
	colors[1] = get_pixel_color(texture, x[1], y[0], space_between_color);
	colors[2] = get_pixel_color(texture, x[0], y[1], space_between_color);
	colors[3] = get_pixel_color(texture, x[1], y[1], space_between_color);
	return (merge_color_with_ratio(&ratio, colors));
}

static t_color	apply_texture_not_found(t_vec2 const *pixel_pos)
{
	t_color	res;

	res = (t_color){0};
	if (((int)(pixel_pos->x * 8.0f) + (int)(pixel_pos->y * 8.0f)) % 2)
	{
		res.r = 255;
		res.g = 85;
		res.b = 255;
	}
	return (res);
}

/**
 * Calculate the pixel position and ratio for the interpolation of the texture
 *
 * @param[in] texture
 * @param[in] pixel_pos
 * @param[out] x int[2]
 * @param[out] y int[2]
 * @returns The pixel position ratio
 */
static t_vec2	compute_ratio_pos_pixel(
					mlx_texture_t const *texture,
					t_vec2 const *pixel_pos,
					int x[2],
					int y[2])
{
	t_vec2		ratio;

	ratio.x = texture->width * pixel_pos->x;
	x[0] = ratio.x;
	ratio.x -= x[0];
	x[1] = x[0] + 1;
	if (x[1] == (int)texture->width)
		x[1] = 0;
	ratio.y = texture->height * pixel_pos->y;
	y[0] = ratio.y;
	ratio.y -= y[0];
	y[1] = y[0] + 1;
	if (y[1] == (int)texture->height)
		y[1] = 0;
	return (ratio);
}

static t_color	get_pixel_color(
					mlx_texture_t const *texture,
					int x,
					int y,
					int space_between_color)
{
	t_color	color;
	int		pixel_index;

	pixel_index = texture->width * y + x;
	color.r = texture->pixels[pixel_index * texture->bytes_per_pixel];
	color.g = texture->pixels[pixel_index * texture->bytes_per_pixel
		+ space_between_color];
	color.b = texture->pixels[pixel_index * texture->bytes_per_pixel
		+ (space_between_color * 2)];
	return (color);
}

static t_color	merge_color_with_ratio(
					t_vec2 const *ratio,
					t_color colors[4])
{
	t_vec2	inv_ratio;

	inv_ratio.x = 1.0f - ratio->x;
	inv_ratio.y = 1.0f - ratio->y;
	colors[0].r = colors[0].r * inv_ratio.x + colors[1].r * ratio->x;
	colors[0].g = colors[0].g * inv_ratio.x + colors[1].g * ratio->x;
	colors[0].b = colors[0].b * inv_ratio.x + colors[1].b * ratio->x;
	colors[1].r = colors[2].r * inv_ratio.x + colors[3].r * ratio->x;
	colors[1].g = colors[2].g * inv_ratio.x + colors[3].g * ratio->x;
	colors[1].b = colors[2].b * inv_ratio.x + colors[3].b * ratio->x;
	colors[0].r = colors[0].r * inv_ratio.y + colors[1].r * ratio->y;
	colors[0].g = colors[0].g * inv_ratio.y + colors[1].g * ratio->y;
	colors[0].b = colors[0].b * inv_ratio.y + colors[1].b * ratio->y;
	return (colors[0]);
}
