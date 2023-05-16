/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdubois <tdubois@student.42angouleme.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 12:45:57 by tdubois           #+#    #+#             */
/*   Updated: 2023/05/16 15:41:34 by tdubois          ###   ########.fr       */
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
						mlx_t const *mlx,
						t_camera const *camera,
						t_vec3 *top_left_vec);
static inline void	_fast_render(
						mlx_t *mlx,
						mlx_image_t *img,
						t_scene *scene);
static inline void	_fill_square(
						mlx_image_t *img,
						int x,
						int y,
						int color);
static inline void	_render_one_pixel(
						mlx_t *mlx,
						mlx_image_t *img,
						t_scene *scene,
						int32_t pixel_rendered);

#define PPR 8 // pixel_per_ray (during fast rendering)

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
		_render_one_pixel(mlx, canvas->back, scene, pixel_rendered);
		++pixel_rendered;
		if (mlx_get_time() > tmax)
			return ;
	}
	is_rendering = false;
	canvas_swap(canvas);
}

static inline void	_render_one_pixel(
						mlx_t *mlx,
						mlx_image_t *img,
						t_scene *scene,
						int32_t pixel_rendered)
{
	t_ray			casted_ray;
	int32_t const	x = pixel_rendered % mlx->width;
	int32_t const	y = pixel_rendered / mlx->width;

	casted_ray.pos = scene->camera->pos;
	casted_ray.vec = scene->camera->pos;
	vec3_linear_transform(&casted_ray.vec, mlx->width / 2.0f - x, &scene->camera->o_x);
	vec3_linear_transform(&casted_ray.vec, mlx->height / 2.0f - y, &scene->camera->o_y);
	vec3_linear_transform(&casted_ray.vec, scene->camera->focal, &scene->camera->direction);
	vec3_substract(&casted_ray.vec, &casted_ray.pos);
	vec3_normalize(&casted_ray.vec);
	if ((uint32_t)x < img->width && (uint32_t)y < img->height)
		mlx_put_pixel(img, x, y, render_ray(scene, &casted_ray));
}

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

	_get_top_left_ray(mlx, scene->camera, &left_ray.vec);
	normalized_casted_ray.pos = scene->camera->pos;
	y = 0;
	while (y < mlx->height)
	{
		casted_ray.vec = left_ray.vec;
		x = 0;
		while (x < mlx->width)
		{
			vec3_normalize_into(&normalized_casted_ray.vec, &casted_ray.vec);
			_fill_square(img, x, y, render_ray(scene, &normalized_casted_ray));
			vec3_linear_transform(&casted_ray.vec, -PPR, &scene->camera->o_x);
			x += PPR;
		}
		vec3_linear_transform(&left_ray.vec, -PPR, &scene->camera->o_y);
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
						mlx_t const *mlx,
						t_camera const *camera,
						t_vec3 *top_left_vec)
{
	*top_left_vec = camera->pos;
	vec3_linear_transform(top_left_vec, mlx->width / 2.0f, &camera->o_x);
	vec3_linear_transform(top_left_vec, mlx->height / 2.0f, &camera->o_y);
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
