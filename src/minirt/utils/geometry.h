/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   geometry.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdubois <tdubois@student.42angouleme.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 01:28:34 by tdubois           #+#    #+#             */
/*   Updated: 2023/06/02 02:37:44 by tdubois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GEOMETRY_H
# define GEOMETRY_H

#include <stdbool.h>

//> GEOMETRY SUB LIBRARY
//>
//> contains:
//>   - mathematical constants
//>   - vec3 typedef and its methods

// constants for faster trigonometry
# define PI 3.141592
# define PI_DIV_180 0.017453
# define PI_DIV_360 0.008726

// model for a vector or point in space
typedef struct s_vec3
{
	float	x;
	float	y;
	float	z;
}	t_vec3;

typedef struct s_vec2
{
	float	x;
	float	y;
}	t_vec2;

typedef struct s_ray
{
	t_vec3	pos;
	t_vec3	vec;
}	t_ray;

extern float	vec3_norm(
					t_vec3 const *vec);
extern float	vec3_normalize(
					t_vec3 *src);
extern float	vec3_normalize_into(
					t_vec3 *restrict dst,
					t_vec3 const *restrict src);
extern float	vec3_dot(
					t_vec3 const *u,
					t_vec3 const *v);
extern float	vec3_dot_xyz(
					float x,
					float y,
					float z,
					t_vec3 const *vec);
extern void		vec3_scale(
					t_vec3 *vec,
					float scaling_factor);
extern void		vec3_add(
					t_vec3 *restrict vec1,
					t_vec3 const *restrict vec2);
extern void		vec3_substract(
					t_vec3 *restrict vec1,
					t_vec3 const *restrict vec2);
extern void		vec3_substract_into(
					t_vec3 *restrict dst,
					t_vec3 const *restrict lhs,
					t_vec3 const *restrict rhs);
extern void		vec3_linear_transform(
					t_vec3 *restrict vec1,
					float scaling_factor,
					t_vec3 const *restrict vec2);

extern t_vec2	vec2(
					float x,
					float y);

extern t_vec3	vec3(
					float x,
					float y,
					float z);

extern bool		solve_quadratic(
					float a,
					float b,
					float c,
					float solutions[2]);

#endif//GEOMETRY_H
