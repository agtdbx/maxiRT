/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   geometry.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auguste <auguste@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 01:28:34 by tdubois           #+#    #+#             */
/*   Updated: 2024/04/21 12:31:49 by auguste          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GEOMETRY_H
# define GEOMETRY_H

# include <stdbool.h>
# include <stdint.h>

// model for a vector or point in space
typedef struct s_vec2
{
	float	x;
	float	y;
}	t_vec2;

typedef struct s_vec3
{
	float	x;
	float	y;
	float	z;
}	t_vec3;

typedef struct s_ray
{
	t_vec3		pos;
	t_vec3		vec;
	uint32_t	depth;
}	t_ray;

extern float	vec2_dot(
					t_vec2 const *u,
					t_vec2 const *v);

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
extern void		vec3_scale_into(
					t_vec3 *res,
					t_vec3 const *restrict vec,
					float scaling_factor);
extern void		vec3_add(
					t_vec3 *restrict vec1,
					t_vec3 const *restrict vec2);
extern void		vec3_add_into(
					t_vec3 *restrict dst,
					t_vec3 const *restrict lhs,
					t_vec3 const *restrict rhs);
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
extern void		vec3_cross(
					t_vec3 const *v1,
					t_vec3 const *v2,
					t_vec3 *vec_res);

extern void		vec3_div_into(
					t_vec3 *lhs,
					t_vec3 *rhs,
					t_vec3 *res);

bool			vec3_equals(
					t_vec3 *a,
					t_vec3 *b);

extern t_vec3	vec3(
					float x,
					float y,
					float z);

extern bool		solve_quadratic(
					float a,
					float b,
					float c,
					float solutions[2]);

t_vec3			mat_product(
					t_vec3 const *mat_1,
					t_vec3 const *mat_2,
					t_vec3 const *mat_3,
					t_vec3 const *lambda);

#endif//GEOMETRY_H
