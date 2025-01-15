/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_normal_map.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouba <aderouba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 16:08:47 by aderouba          #+#    #+#             */
/*   Updated: 2023/07/05 20:48:25 by aderouba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt/app/app.h"

#include "minirt/app/utils/geometry/geometry.h"

static t_vec2	compute_ratio_pos_pixel(
					mlx_texture_t const *texture,
					t_vec2 const *pixel_pos,
					int x[2],
					int y[2]);
static t_vec3	get_pixel_normal(
					mlx_texture_t const *texture,
					int x,
					int y,
					int space_between_color);
static t_vec3	merge_normals_with_ratio(
					t_vec2 const *ratio,
					t_vec3 normals[4]);

void	apply_normal_map(
					mlx_texture_t const *normal_map,
					t_vec2 const *pixel_pos,
					t_ray *normal)
{
	t_vec2		ratio;
	t_vec3		normals[4];
	int			x[2];
	int			y[2];
	int			space_between_color;

	if (!normal_map)
		return ;
	space_between_color = normal_map->bytes_per_pixel / 4;
	ratio = compute_ratio_pos_pixel(normal_map, pixel_pos, x, y);
	normals[0] = get_pixel_normal(normal_map, x[0], y[0], space_between_color);
	normals[1] = get_pixel_normal(normal_map, x[1], y[0], space_between_color);
	normals[2] = get_pixel_normal(normal_map, x[0], y[1], space_between_color);
	normals[3] = get_pixel_normal(normal_map, x[1], y[1], space_between_color);
	normal->vec = merge_normals_with_ratio(&ratio, normals);
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

static t_vec3	get_pixel_normal(
					mlx_texture_t const *texture,
					int x,
					int y,
					int space_between_color)
{
	t_vec3	normal;
	int		pixel_index;

	pixel_index = texture->width * y + x;
	normal.x = texture->pixels[pixel_index * texture->bytes_per_pixel] / 255.0f;
	normal.y = texture->pixels[pixel_index * texture->bytes_per_pixel
		+ space_between_color] / 255.0f;
	normal.z = texture->pixels[pixel_index * texture->bytes_per_pixel
		+ (space_between_color * 2)] / 255.0f;
	return (normal);
}

static t_vec3	merge_normals_with_ratio(
					t_vec2 const *ratio,
					t_vec3 normals[4])
{
	t_vec2	inv_ratio;

	inv_ratio.x = 1.0f - ratio->x;
	inv_ratio.y = 1.0f - ratio->y;
	normals[0].x = normals[0].x * inv_ratio.x + normals[1].x * ratio->x;
	normals[0].y = normals[0].y * inv_ratio.x + normals[1].y * ratio->x;
	normals[0].z = normals[0].z * inv_ratio.x + normals[1].z * ratio->x;
	normals[1].x = normals[2].x * inv_ratio.x + normals[3].x * ratio->x;
	normals[1].y = normals[2].y * inv_ratio.x + normals[3].y * ratio->x;
	normals[1].z = normals[2].z * inv_ratio.x + normals[3].z * ratio->x;
	normals[0].x = normals[0].x * inv_ratio.y + normals[1].x * ratio->y;
	normals[0].y = normals[0].y * inv_ratio.y + normals[1].y * ratio->y;
	normals[0].z = normals[0].z * inv_ratio.y + normals[1].z * ratio->y;
	return (normals[0]);
}
