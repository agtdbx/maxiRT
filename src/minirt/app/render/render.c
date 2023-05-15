/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdubois <tdubois@student.42angouleme.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 12:45:57 by tdubois           #+#    #+#             */
/*   Updated: 2023/05/15 17:30:16 by tdubois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt/app/app.h>
#include <minirt/scene/scene.h>
#include <minirt/utils/geometry.h>

#include <MLX42/MLX42.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>//TODO
#include <math.h>//TODO
#include <stdlib.h>//TODO

static inline void	_get_top_left_ray(
						mlx_t const *mlx,
						t_camera const *camera,
						t_ray *top_left);
static inline void	_fast_render(
						mlx_t *mlx,
						mlx_image_t *img,
						t_scene *scene);
static inline void	_fill_square(
						mlx_image_t *img,
						int x,
						int y,
						int color);

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
	// canvas_swap(canvas);
}

#define PRINT_VEC(VEC)\
	printf("(%s) x: %f | y: %f | z: %f\n", #VEC, VEC.x , VEC.y, VEC.z);

#define PPR 4

static inline void	_fast_render(
						mlx_t *mlx,
						mlx_image_t *img,
						t_scene *scene)
{
	t_ray	left_ray;
	t_ray	casted_ray;
	t_ray	normalized_casted_ray;
	int		x;
	int		y;
	int	DEBUG_i = 0;

	// PRINT_VEC(scene->camera->o_x)
	// PRINT_VEC(scene->camera->o_y)
	_get_top_left_ray(mlx, scene->camera, &left_ray);
	y = 0;
	while (y < mlx->height)
	{
		casted_ray.vec = left_ray.vec;
		normalized_casted_ray.pos = left_ray.pos;
		x = 0;
		while (x < mlx->width)
		{
			vec3_normalize_into(&normalized_casted_ray.vec, &casted_ray.vec);
			if (abs(x - mlx->width/ 2) < 20 && abs(y - mlx->height/2) < 20)
			{
				// PRINT_VEC(normalized_casted_ray.pos)
				// PRINT_VEC(casted_ray.vec)
			}
			if (DEBUG_i == 60210)
				_fill_square(img, x, y, 0xFF0000FF);
			else
				_fill_square(img, x, y, render_ray(scene, &normalized_casted_ray));
			vec3_linear_transform(&casted_ray.vec, -PPR, &scene->camera->o_x);
			vec3_linear_transform(&normalized_casted_ray.pos, -PPR, &scene->camera->o_x);
			x += PPR;

			++DEBUG_i;
		}
		vec3_linear_transform(&left_ray.vec, -PPR, &scene->camera->o_y);
		vec3_linear_transform(&left_ray.pos, -PPR, &scene->camera->o_y);
		y += PPR;
	}
}

/**
 *  Compute the ray associated with the topleft corner pixel.
 *  @param[in] mlx The mlx harness
 *  @param[in] camera The camera instance
 *  @param[out] top_left The un-normalized computed ray
 */
static inline void	_get_top_left_ray(
						mlx_t const *mlx,
						t_camera const *camera,
						t_ray *top_left)
{
	top_left->pos = camera->pos;
	vec3_linear_transform(&top_left->pos, mlx->width / (2.0f), &camera->o_x);
	vec3_linear_transform(&top_left->pos, mlx->height / (2.0f), &camera->o_y);
	top_left->vec = top_left->pos;
	vec3_substract(&top_left->vec, &camera->pos);
	vec3_linear_transform(&top_left->vec, camera->focal, &camera->direction);
}

static inline void	_fill_square(
						mlx_image_t *img,
						int x,
						int y,
						int color)
{
	register int const initial_x = x;
	register int const max_x = x + PPR;
	register int const max_y = y + PPR;

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
