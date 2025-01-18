/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   antialiasing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damien <damien@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 21:47:01 by damien            #+#    #+#             */
/*   Updated: 2025/01/18 01:18:18 by damien           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt/app/app.h"
#include "minirt/app/utils/color/color.h"

static t_vec3	_get_pixel_color(mlx_image_t *img, t_vec2 pos);
static void		_sample_pixel(t_vec2 pixel, t_canvas *canvas);

void antialiasing(t_canvas *canvas)
{
	int	i, j;

	for (i = 0; i < canvas->width; i++)
		for (j = 0; j < canvas->height; j++)
			_sample_pixel((t_vec2) {i, j}, canvas);
}

static void	_sample_pixel(t_vec2 pix, t_canvas *canvas)
{
	int				x, y;
	t_vec2			neighb_pix;
	t_vec3			new_color_vec = {0};
	t_vec3			pixel_color_vec, neighb_pixel_color_vec;
	t_vec3			dir, neighb_dir;
	t_vec3			tmp;
	t_color			new_color;
	static t_vec3	zvec = {0, 0, 0};
	float			norm, neighb_norm;

	if (!vec3_equals(&pixel_color_vec, &zvec))
		vec3_div_into(&pixel_color_vec, &pixel_color_vec, &dir);
	else{
		dir.x = 0;
		dir.y = 0;
	}
	norm = vec3_norm(&dir);
	pixel_color_vec = _get_pixel_color(canvas->back, pix);
	for (x = -1; x < 2; x++)
	{
		for (y = -1; y < 2; y++)
		{
			neighb_pix = (t_vec2) {pix.x + x, pix.y + y};
			if (neighb_pix.x < 0 || neighb_pix.x > canvas->width
				|| neighb_pix.y < 0 || neighb_pix.y > canvas->height)
				continue;
			neighb_pixel_color_vec = _get_pixel_color(canvas->back, neighb_pix);
			if (!vec3_equals(&neighb_pixel_color_vec, &zvec))
				vec3_div_into(&neighb_pixel_color_vec, &neighb_pixel_color_vec, &neighb_dir);
			else{
				neighb_dir.x = 0;
				neighb_dir.y = 0;
			}
			if (vec3_dot(&dir, &neighb_dir) > 0.1)
			{
				neighb_norm = vec3_norm(&neighb_dir);
				if (fabs(norm - neighb_norm) < 0.1)
					continue ;
			}
			if (vec3_equals(&new_color_vec, &zvec))
				mix_color_into(&new_color_vec, &pixel_color_vec, &neighb_pixel_color_vec, 0.5);
			else
			{
				mix_color_into(&tmp, &pixel_color_vec, &neighb_pixel_color_vec, 0.3);
				mix_color_into(&new_color_vec, &new_color_vec, &tmp, 0.5);
			}
		}
	}
	new_color = (t_color) {new_color_vec.x, new_color_vec.y, new_color_vec.z, 1};
	mlx_put_pixel(canvas->front, pix.x, pix.y, color_to_int(&new_color));
}

static t_vec3	_get_pixel_color(mlx_image_t *img, t_vec2 pos)
{
	t_vec3	color;
	int		index;
	int		coords[2];

	coords[0] = pos.x;
	coords[1] = pos.y;
	index = (coords[1] * img->width + coords[0]) * sizeof(uint32_t);
	color.x = (float)img->pixels[index];
	color.y = (float)img->pixels[index + 1];
	color.z = (float)img->pixels[index + 2];
	return (color);
}
