/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdubois <tdubois@student.42angouleme.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 12:45:57 by tdubois           #+#    #+#             */
/*   Updated: 2023/06/05 09:10:25 by tdubois          ###   ########.fr       */
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

static void	_print_rendering_progress(
				mlx_t *mlx,
				bool is_rendering,
				int32_t	pixel_rendered);
static void	_get_top_left_ray(
				t_canvas const *canvas,
				t_camera const *camera,
				t_vec3 *top_left_vec);
static void	_fast_render(
				mlx_t *mlx,
				t_canvas const *canvas,
				t_scene const *scene,
				bool show_spotlights);

void	render_canvas(
			t_app *app,
			bool should_render)
{
	static bool		is_rendering = true;
	static int32_t	pixel_rendered = 0;
	double			tmax;

	if (should_render)
	{
		is_rendering = true;
		pixel_rendered = 0;
		_fast_render(app->mlx, &app->canvas, &app->scene, app->menu.is_visible);
		return ;
	}
	_print_rendering_progress(app->mlx, is_rendering, pixel_rendered);
	if (!is_rendering)
		return ;
	tmax = mlx_get_time() - app->mlx->delta_time + 0.15;
	while (pixel_rendered < app->mlx->width * app->mlx->height)
	{
		render_one_pixel(
			&app->scene, &app->canvas, pixel_rendered, app->menu.is_visible);
		++pixel_rendered;
		if (mlx_get_time() > tmax)
			return ;
	}
	is_rendering = false;
	canvas_swap(&app->canvas);
}

static void	_print_rendering_progress(
				mlx_t *mlx,
				bool is_rendering,
				int32_t	pixel_rendered)
{
	static mlx_image_t	*img = NULL;
	float				progress;
	char				str[30];
	size_t				len;

	if (img != NULL)
	{
		mlx_delete_image(mlx, img);
		img = NULL;
	}
	if (!is_rendering)
		return ;
	progress = pixel_rendered;
	progress /= mlx->width * mlx->height;
	len = ft_sitoa(progress * 100.0f, str, sizeof(str));
	ft_strlcpy(str + len, " %", sizeof(str) - len);
	img = mlx_put_string(mlx, str, 10, 10);
	mlx_set_instance_depth(img->instances, 3);
}

/**
 *  Compute the direction of the ray associated with the topleft corner pixel.
 *  @param[in] mlx The mlx harness
 *  @param[in] camera The camera instance
 *  @param[out] top_left The un-normalized computed ray
 */
static void	_get_top_left_ray(
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

static void	_fast_render(
				mlx_t *mlx,
				t_canvas const *canvas,
				t_scene const *scene,
				bool show_spotlights)
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
			img_draw_square(canvas->front, pix, ppr,
				render_ray_from_camera(scene, &casted_ray, show_spotlights));
			vec3_linear_transform(&ray[X], -ppr, &scene->camera->o_x);
			pix[X] += ppr;
		}
		vec3_linear_transform(&ray[Y], -ppr, &scene->camera->o_y);
		pix[Y] += ppr;
	}
}
