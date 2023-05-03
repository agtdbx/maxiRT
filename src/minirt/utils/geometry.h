/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   geometry.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdubois <tdubois@student.42angouleme.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 01:28:34 by tdubois           #+#    #+#             */
/*   Updated: 2023/05/03 13:10:59 by tdubois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GEOMETRY_H
# define GEOMETRY_H

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

extern float	vec3_norm(
					t_vec3 const *vec);

extern float	vec3_dot_xyz(
						float x,
						float y,
						float z,
						t_vec3 const *vec);

#endif//GEOMETRY_H
