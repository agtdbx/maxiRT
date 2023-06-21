/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_rotations.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdubois <tdubois@student.42angouleme.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 16:42:13 by tdubois           #+#    #+#             */
/*   Updated: 2023/06/21 16:11:03 by tdubois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt/app/app.h"

#include <stdbool.h>
#include <math.h>

#include "MLX42/MLX42.h"

#include "minirt/app/app_config.h"

static inline bool	_rotate_around_ox(
						mlx_t *mlx,
						t_camera *camera,
						float rads);
static inline bool	_rotate_around_oy(
						mlx_t *mlx,
						t_camera *camera,
						float rads);
static inline void	_relative_rotate(
						t_vec3 *restrict vec,
						t_vec3 const *restrict axis,
						float rads);
static inline void	_absolute_rotate_around_oy(
						t_vec3 *vec,
						float rads);

/**
 * Updates camera direction based on keyboard input.
 * @param[in] mlx The mlx handle
 * @param[out] camera The camera to be updated
 * @returns true or false wether scene should be rendered or not
 */
bool	handle_rotations(
			mlx_t *mlx,
			t_canvas const *canvas,
			t_camera *camera)
{
	float const	rads = -mlx->delta_time * 40.0f * g_pi_div_180;
	bool		should_render;

	should_render = false;
	should_render |= _rotate_around_ox(mlx, camera, rads);
	should_render |= _rotate_around_oy(mlx, camera, rads);
	if (should_render)
		camera_compute_constants(canvas, camera);
	return (should_render);
}

static inline bool	_rotate_around_ox(
						mlx_t *mlx,
						t_camera *camera,
						float rads)
{
	t_vec3 *const	direction = &camera->direction;
	t_vec3 *const	o_x = &camera->o_x;

	if (mlx_is_key_down(mlx, MLX_KEY_UP))
	{
		if (!mlx_is_key_down(mlx, MLX_KEY_DOWN))
		{
			_relative_rotate(direction, o_x, -rads);
			return (true);
		}
	}
	else if (mlx_is_key_down(mlx, MLX_KEY_DOWN))
	{
		_relative_rotate(direction, o_x, +rads);
		return (true);
	}
	return (false);
}

static inline bool	_rotate_around_oy(
						mlx_t *mlx,
						t_camera *camera,
						float rads)
{
	t_vec3 *const	direction = &camera->direction;

	if (mlx_is_key_down(mlx, MLX_KEY_LEFT))
	{
		if (!mlx_is_key_down(mlx, MLX_KEY_RIGHT))
		{
			_absolute_rotate_around_oy(direction, -rads);
			return (true);
		}
	}
	else if (mlx_is_key_down(mlx, MLX_KEY_RIGHT))
	{
		_absolute_rotate_around_oy(direction, rads);
		return (true);
	}
	return (false);
}

/**
 * Rotates 3d vector vec by angle rads, around axis using quaternions
 * derived arithmetic.
 * @param[out] vec The vector to be rotated
 * @param[in] axis The orientation vector of the axis to rotate around
 * @param[in] rads The angle that should be rotated
 */
static inline void	_relative_rotate(
						t_vec3 *restrict vec,
						t_vec3 const *restrict axis,
						float rads)
{
	float	t[13];
	t_vec3	ret;

	t[0] = cosf(rads);
	t[1] = 1.0f - t[0];
	t[2] = axis->x * axis->x;
	t[3] = t[1] * axis->x;
	t[4] = t[3] * axis->y;
	t[5] = sinf(rads);
	t[6] = t[5] * axis->z;
	t[7] = t[3] * axis->z;
	t[8] = t[5] * axis->y;
	t[9] = axis->y * axis->y;
	t[10] = t[1] * axis->y * axis->z;
	t[11] = t[5] * axis->x;
	t[12] = axis->z * axis->z;
	ret.x = vec3_dot_xyz(t[0] + t[1] * t[2], t[4] - t[6], t[7] + t[8], vec);
	ret.y = vec3_dot_xyz(t[4] + t[6], t[0] + t[1] * t[9], t[10] - t[11], vec);
	ret.z = vec3_dot_xyz(t[7] - t[8], t[10] + t[11], t[0] + t[1] * t[12], vec);
	*vec = ret;
}

/**
 * Rotates 3d vector vec by angle rads, around Oy (vertical) axis using
 * quaternions derived arithmetic.
 * @param[out] vec The vector to be rotated
 * @param[in] rafs The angle that should be rotated
 */
static inline void	_absolute_rotate_around_oy(
						t_vec3 *vec,
						float rads)
{
	float const	tmp_cos = cosf(rads);
	float const	tmp_sin = sinf(rads);
	float		tmp_x;
	float		tmp_z;

	tmp_x = tmp_cos * vec->x + tmp_sin * vec->z;
	tmp_z = -tmp_sin * vec->x + tmp_cos * vec->z;
	vec->x = tmp_x;
	vec->z = tmp_z;
}
