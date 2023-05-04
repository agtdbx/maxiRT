/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdubois <tdubois@student.42angouleme.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 12:45:57 by tdubois           #+#    #+#             */
/*   Updated: 2023/05/04 17:56:55 by tdubois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt/app/app.h>
#include <minirt/scene/scene.h>
#include <minirt/utils/geometry.h>

#include <MLX42/MLX42.h>
#include <stdbool.h>
#include <stdint.h>

static inline t_ray	_get_top_left_ray(
						mlx_t *mlx,
						t_camera *camera);
static inline void	_fast_render(
						mlx_t *mlx,
						mlx_image_t *img,
						t_scene *scene);
// static inline void	_fill_square(
// 						mlx_image_t *img,
// 						int x,
// 						int y,
// 						int color);

void	render(
			mlx_t *mlx,
			t_canvas *canvas,
			t_scene *scene,
			bool should_render)
{
	static bool		is_rendering = true;
	static int32_t	pixel_rendered = 0;
	double			tmax;

	if (should_render)
	{
		is_rendering = true;
		pixel_rendered = 0;
		_fast_render(mlx, canvas->front, scene);
		return ;
	}
	if (!is_rendering)
		return ;
	tmax = mlx_get_time() - mlx->delta_time + 0.25;
	while (pixel_rendered < mlx->width * mlx->height)
	{
		//render_one_pixel
		++pixel_rendered;
		if (mlx_get_time() > tmax)
			return ;
	}
	is_rendering = false;
	// canvas_swap(&app->canvas);
}

#define PPR 4

static inline void	_fast_render(
						mlx_t *mlx,
						mlx_image_t *img,
						t_scene *scene)
{
	t_ray	left_ray;
	t_ray	casted_ray;
	int		x;
	int		y;

	left_ray = _get_top_left_ray(mlx, scene->camera);
	casted_ray = left_ray;
	y = 0;
	while (y < mlx->height)
	{
		x = 0;
		while (x < mlx->width)
		{
			(void) img;
			// _fill_square(img, x, y, render_pixel(scene, &casted_ray));
			vec3_linear_transform(&casted_ray.vec, -PPR, &scene->camera->o_x);
			x += PPR;
		}
		vec3_linear_transform(&casted_ray.vec, -PPR, &scene->camera->o_y);
		y += PPR;
	}
}

static inline t_ray	_get_top_left_ray(
						mlx_t *mlx,
						t_camera *camera)
{
	t_vec3	focal_pos;
	t_ray	top_left;

	focal_pos = camera->direction;
	vec3_scale(&focal_pos, -camera->focal);
	vec3_add(&focal_pos, &camera->pos);
	top_left.pos = camera->pos;
	vec3_linear_transform(&top_left.pos, (float)mlx->width / 2, &camera->o_x);
	vec3_linear_transform(&top_left.pos, (float)mlx->height / 2, &camera->o_y);
	top_left.vec = top_left.pos;
	vec3_sub(&top_left.vec, &focal_pos);
	return (top_left);
}

// static inline void	_fill_square(
// 						mlx_image_t *img,
// 						int x,
// 						int y,
// 						int color)
// {
// 	int const initial_x = x;
// 	int const max_x = x + PPR;
// 	int const max_y = y + PPR;
//
// 	while (y < max_y)
// 	{
// 		x = initial_x;
// 		while (x < max_x)
// 		{
// 			mlx_put_pixel(img, x, y, color);
// 			++x;
// 		}
// 		++y;
// 	}
// }
