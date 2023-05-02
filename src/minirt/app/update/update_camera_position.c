/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_camera_position.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdubois <tdubois@student.42angouleme.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 16:42:13 by tdubois           #+#    #+#             */
/*   Updated: 2023/05/03 01:05:25 by tdubois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt/app/app.h>
#include <MLX42/MLX42.h>
#include <math.h>

static inline void	_safe_assign(
						float *dst,
						float src);
static inline bool	_update_camera_position_x(
						mlx_t *mlx,
						t_camera *camera,
						float speed);
static inline bool	_update_camera_position_y(
						mlx_t *mlx,
						t_camera *camera,
						float speed);
static inline bool	_update_camera_position_z(
						mlx_t *mlx,
						t_camera *camera,
						float speed);

/**
 * Updates camera position based on keyboard input.
 * @param[in] mlx The mlx handle
 * @param[out] camera The camera to be updated
 * @returns true or false wether scene should be rendered or not
 */
bool	update_camera_position(
			mlx_t *mlx,
			t_camera *camera)
{
	float const	speed = mlx->delta_time * 5.0f;

	return (false
		| _update_camera_position_x(mlx, camera, speed)
		| _update_camera_position_y(mlx, camera, speed)
		| _update_camera_position_z(mlx, camera, speed));
}

/**
 * Assign src to *dst if src is a finite float
 * @param[in] src The value to assign from
 * @param[out] dst The variable to assign to
 */
static inline void	_safe_assign(
						float *dst,
						float src)
{
	if (isfinite(src))
		*dst = src;
}

static inline bool	_update_camera_position_x(
						mlx_t *mlx,
						t_camera *camera,
						float speed)
{
	t_vec3 *const	position = &camera->pos;
	t_vec3 *const	o_x = &camera->o_x;

	if (mlx_is_key_down(mlx, MLX_KEY_A) || mlx_is_key_down(mlx, MLX_KEY_Q))
	{
		if (!mlx_is_key_down(mlx, MLX_KEY_D))
		{
			_safe_assign(&position->x, position->x - o_x->x * speed);
			_safe_assign(&position->z, position->z - o_x->z * speed);
			return (true);
		}
	}
	else if (mlx_is_key_down(mlx, MLX_KEY_D))
	{
		_safe_assign(&position->x, position->x + o_x->x * speed);
		_safe_assign(&position->z, position->z + o_x->z * speed);
		return (true);
	}
	return (false);
}

static inline bool	_update_camera_position_y(
						mlx_t *mlx,
						t_camera *camera,
						float speed)
{
	t_vec3 *const	position = &camera->pos;

	if (mlx_is_key_down(mlx, MLX_KEY_SPACE))
	{
		if (!mlx_is_key_down(mlx, MLX_KEY_LEFT_SHIFT))
		{
			_safe_assign(&position->y, position->y + speed);
			return (true);
		}
	}
	else if (mlx_is_key_down(mlx, MLX_KEY_LEFT_SHIFT))
	{
		_safe_assign(&position->y, position->y - speed);
		return (true);
	}
	return (false);
}

static inline bool	_update_camera_position_z(
						mlx_t *mlx,
						t_camera *camera,
						float speed)
{
	t_vec3 *const	position = &camera->pos;
	t_vec3 *const	direction = &camera->direction;

	if (mlx_is_key_down(mlx, MLX_KEY_W) || mlx_is_key_down(mlx, MLX_KEY_Z))
	{
		if (!mlx_is_key_down(mlx, MLX_KEY_S))
		{
			_safe_assign(&position->x, position->x + direction->x * speed);
			_safe_assign(&position->z, position->z + direction->z * speed);
			return (true);
		}
	}
	else if (mlx_is_key_down(mlx, MLX_KEY_S))
	{
		_safe_assign(&position->x, position->x - direction->x * speed);
		_safe_assign(&position->z, position->z - direction->z * speed);
		return (true);
	}
	return (false);
}
