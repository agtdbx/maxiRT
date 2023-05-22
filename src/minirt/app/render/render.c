/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdubois <tdubois@student.42angouleme.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 12:45:57 by tdubois           #+#    #+#             */
/*   Updated: 2023/05/22 09:23:15 by tdubois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt/app/app.h>
#include <minirt/scene/scene.h>
#include <minirt/utils/geometry.h>

#include <libft/libft.h>
#include <MLX42/MLX42.h>
#include <stdbool.h>
#include <stdint.h>

//----------------------------------------------------------------------------//
//TODO

#include <stdio.h>//TODO
#include <math.h>//TODO
#include <stdlib.h>//TODO
#define PRINT_VEC(VEC)\
	printf("(%s) x: %f | y: %f | z: %f\n", #VEC, VEC.x , VEC.y, VEC.z);

//----------------------------------------------------------------------------//

static inline void	_get_top_left_ray(
						t_canvas const *canvas,
						t_camera const *camera,
						t_vec3 *top_left_vec);
static inline void	_fast_render(
						t_canvas const *canvas,
						t_scene const *scene);
static inline void	_fill_square(
						mlx_image_t *img,
						int x,
						int y,
						int color);
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
		_fast_render(canvas, scene);
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

static inline void	_fast_render(
						t_canvas const *canvas,
						t_scene const *scene)
{
	t_vec3	y_ray;
	t_vec3	x_ray;
	t_ray	casted_ray;
	int		x;
	int		y;

	_get_top_left_ray(canvas, scene->camera, &y_ray);
	casted_ray.pos = scene->camera->pos;
	y = 0;
	while (y < canvas->height)
	{
		x_ray = y_ray;
		x = 0;
		while (x < canvas->width)
		{
			vec3_normalize_into(&casted_ray.vec, &x_ray);
			_fill_square(canvas->front, x, y, render_ray(scene, &casted_ray));
			vec3_linear_transform(&x_ray, -PPR, &scene->camera->o_x);
			x += PPR;
		}
		vec3_linear_transform(&y_ray, -PPR, &scene->camera->o_y);
		y += PPR;
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

static inline void	_fill_square(
						mlx_image_t *img,
						int x,
						int y,
						int color)
{
	register int const	initial_x = x;
	register int const	max_x = ft_min(x + PPR, img->width);
	register int const	max_y = ft_min(y + PPR, img->height);

	while (y < max_y)
	{
		x = initial_x;
		while (x < max_x)
		{
			mlx_put_pixel(img, x, y, color);
			++x;
		}
		++y;
	}
}
