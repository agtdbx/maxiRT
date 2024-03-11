/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_triangle_pixel_pos_bonus.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auguste <auguste@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 15:48:59 by aderouba          #+#    #+#             */
/*   Updated: 2024/03/11 17:44:37 by auguste          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt/app/app_bonus.h"

#include <math.h>

#include "minirt/app/utils/geometry/geometry_bonus.h"

t_vec2	get_triangle_pixel_pos(
					t_triangle const *triangle,
					t_ray const *normal)
{
	t_vec2	pixel;

	float	BCy = triangle->point2.y - triangle->point3.y;
	float	PCx = normal->pos.x - triangle->point3.x;
	float	CBx = triangle->point3.x - triangle->point2.x;
	float	PCy = normal->pos.y - triangle->point3.y;
	float	ACy = triangle->point1.y - triangle->point3.y;
	float	CAy = triangle->point3.y - triangle->point1.y;
	float	ACx = triangle->point1.x - triangle->point3.x;

	float div_part = (BCy * ACx) + (CBx * ACy);

	float bary_a = ((BCy * PCx) + (CBx* PCy)) / div_part;
	float bary_b = ((CAy * PCx) + (ACx * PCy)) / div_part;
	float bary_c = 1 - bary_a - bary_b;

	t_vec3 uv1 = (t_vec3){1.0f, 0.0f, 0.0f};
	t_vec3 uv2 = (t_vec3){0.0f, 1.0f, 0.0f};
	t_vec3 uv3 = (t_vec3){0.0f, 0.0f, 1.0f};

	pixel.x = bary_a * uv1.x
			+ bary_b * uv2.x
			+ bary_c * uv3.x;
	pixel.y = bary_a * uv1.y
			+ bary_b * uv2.y
			+ bary_c * uv3.y;
	return (pixel);
}
