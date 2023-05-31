/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdubois <tdubois@student.42angouleme.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 12:45:57 by tdubois           #+#    #+#             */
/*   Updated: 2023/05/31 23:15:51 by tdubois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt/app/app.h>

#include <minirt/scene/scene.h>
#include <minirt/utils/drawings.h>
#include <minirt/utils/geometry.h>

#include <MLX42/MLX42.h>
#include <libft/libft.h>
#include <stdbool.h>
#include <stdint.h>

static inline void	_get_top_left_ray(
						t_canvas const *canvas,
						t_camera const *camera,
						t_vec3 *top_left_vec);
static inline void	_fast_render(
						mlx_t *mlx,
						t_canvas const *canvas,
						t_scene const *scene);
static inline void	_render_one_pixel(
						t_scene const *scene,
						t_canvas const *canvas,
						int32_t pixel_rendered);

#define PPR 8 // pixel_per_ray (during fast rendering)

void	render(
			mlx_t *mlx,
			t_canvas *canvas,
			t_scene const *scene,
			bool should_render)
{
	static bool		is_rendering = true;
	static int32_t	pixel_rendered = 0;
	double			tmax;

	if (should_render)
	{
		is_rendering = true;
		pixel_rendered = 0;
		_fast_render(mlx, canvas, scene);
		return ;
	}
	if (!is_rendering)
		return ;
	tmax = mlx_get_time() - mlx->delta_time + 0.25;
	while (pixel_rendered < mlx->width * mlx->height)
	{
		_render_one_pixel(scene, canvas, pixel_rendered);
		++pixel_rendered;
		if (mlx_get_time() > tmax)
			return ;
	}
	is_rendering = false;
	canvas_swap(canvas);
}

static inline void	_render_one_pixel(
						t_scene const *scene,
						t_canvas const *canvas,
						int32_t pixel_rendered)
{
	t_ray			casted_ray;
	int32_t const	x = pixel_rendered % canvas->width;
	int32_t const	y = pixel_rendered / canvas->width;

	casted_ray.pos = scene->camera->pos;
	casted_ray.vec = scene->camera->pos;
	vec3_linear_transform(
			&casted_ray.vec, canvas->width_div_2 - x, &scene->camera->o_x);
	vec3_linear_transform(
			&casted_ray.vec, canvas->height_div_2 - y, &scene->camera->o_y);
	vec3_linear_transform(
			&casted_ray.vec, scene->camera->focal, &scene->camera->direction);
	vec3_substract(&casted_ray.vec, &casted_ray.pos);
	vec3_normalize(&casted_ray.vec);
	if (x < canvas->width && y < canvas->height)
		mlx_put_pixel(canvas->back, x, y, render_ray(scene, &casted_ray));
}

#define X 0
#define Y 1

#define FPS_10 0.1
#define FPS_25 0.04

/**
 * auto update ppr according to last dt
 * @param[in] mlx
 * @param[out] ppr
 */
static inline void	_update_ppr(
						mlx_t *mlx,
						int32_t *ppr)
{
	if (FPS_10 < mlx->delta_time)
		++(*ppr);
	else if (*ppr > 1 && mlx->delta_time < FPS_25)
		--(*ppr);
}

static inline void	_fast_render(
						mlx_t *mlx,
						t_canvas const *canvas,
						t_scene const *scene)
{
	static int32_t	ppr = 16;
	t_vec3			ray[2];
	int32_t			pix[2];
	t_ray			casted_ray;

	_update_ppr(mlx, &ppr);
	_get_top_left_ray(canvas, scene->camera, &ray[Y]);
	casted_ray.pos = scene->camera->pos;
	pix[Y] = 0;
	while (pix[Y] < canvas->height)
	{
		ray[X] = ray[Y];
		pix[X] = 0;
		while (pix[X] < canvas->width)
		{
			vec3_normalize_into(&casted_ray.vec, &ray[X]);
			img_draw_square(canvas->front, pix, ppr, render_ray(scene, &casted_ray));
			vec3_linear_transform(&ray[X], -ppr, &scene->camera->o_x);
			pix[X] += ppr;
		}
		vec3_linear_transform(&ray[Y], -ppr, &scene->camera->o_y);
		pix[Y] += ppr;
	}
}

/**
 *  Compute the direction of the ray associated with the topleft corner pixel.
 *  @param[in] mlx The mlx harness
 *  @param[in] camera The camera instance
 *  @param[out] top_left The un-normalized computed ray
 */
static inline void	_get_top_left_ray(
						t_canvas const *canvas,
						t_camera const *camera,
						t_vec3 *top_left_vec)
{
	*top_left_vec = camera->pos;
	vec3_linear_transform(top_left_vec, canvas->width_div_2, &camera->o_x);
	vec3_linear_transform(top_left_vec, canvas->height_div_2, &camera->o_y);
	vec3_linear_transform(top_left_vec, camera->focal, &camera->direction);
	vec3_substract(top_left_vec, &camera->pos);
}
