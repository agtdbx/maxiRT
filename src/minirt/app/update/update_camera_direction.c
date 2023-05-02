/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_camera_direction.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdubois <tdubois@student.42angouleme.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 16:42:13 by tdubois           #+#    #+#             */
/*   Updated: 2023/05/02 23:26:06 by tdubois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt/app/app.h>
#include <MLX42/MLX42.h>
#include <math.h>

// static inline void	_rotate_around_ox(mlx_t *mlx, t_camera *camera, float rads);
// static inline void	_rotate_around_oy(mlx_t *mlx, t_camera *camera, float rads);
//
// /**
//  * Updates camera direction based on keyboard input.
//  * @param[in] mlx The mlx handle
//  * @param[out] camera The camera to be updated
//  */
// void	update_camera_direction(mlx_t *mlx, t_camera *camera)
// {
// 	float const	rads = mlx->delta_time * 20.0f * PI_DIV_180;
//
// 	if (mlx_is_key_down(mlx, MLX_KEY_UP)
// 		|| mlx_is_key_down(mlx, MLX_KEY_DOWN))
// 		_rotate_around_ox(mlx, camera, rads);
// 	if (mlx_is_key_down(mlx, MLX_KEY_LEFT)
// 		|| mlx_is_key_down(mlx, MLX_KEY_RIGHT))
// 		_rotate_around_oy(mlx, camera, rads);
// }
//
// static inline void	_rotate_around_ox(mlx_t *mlx, t_camera *camera, float rads)
// {
// 	t_vec3 *const	position = &camera->pos;
// 	t_vec3 *const	o_x = &camera->o_x;
//
// 	if (mlx_is_key_down(mlx, MLX_KEY_UP))
// 	{
// 	}
// 	else
// 	{
// 	}
// }
//
// static inline void	_rotate_around_oy(mlx_t *mlx, t_camera *camera, float rads)
// {
// 	t_vec3 *const	position = &camera->pos;
//
// 	if (mlx_is_key_down(mlx, MLX_KEY_RIGHT))
// 	{
// 	}
// 	else
// 	{
// 	}
// }
//
// static inline void	_relative_rotate(t_vec3 *restrict vec, t_vec3 const *restrict axis,
// 						float rads)
// {
// 	float	t[13];
// 	t_vec3	ret;
//
// 	t[0] = cos(rads);
// 	t[1] = 1.0f - t[0];
// 	t[2] = axis->x * axis->x;
// 	t[3] = t[1] * axis->x;
// 	t[4] = t[3] * axis->y;
// 	t[5] = sin(rads);
// 	t[6] = t[5] * axis->z;
// 	t[7] = t[3] * axis->z;
// 	t[8] = t[5] * axis->y;
// 	t[9] = axis->y * axis->y;
// 	t[10] = t[1] * axis->y * axis->z;
// 	t[11] = t[5] * axis->x;
// 	t[12] = axis->z * axis->z;
// 	ret.x = vec3_dot(t[0] + t[1] * t[2], t[4] - t[6], t[7] + t[8], vec);
// 	ret.y = vec3_dot(t[4] + t[6], t[0] + t[1] * t[9], t[10] - t[11], vec);
// 	ret.z = vec3_dot(t[7] - t[8], t[10] + t[11], t[0] + t[1] * t[12], vec);
// 	*vec = ret;
// }
