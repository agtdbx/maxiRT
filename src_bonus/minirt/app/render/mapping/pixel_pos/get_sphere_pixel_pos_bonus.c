/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_sphere_pixel_pos.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouba <aderouba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 15:47:41 by aderouba          #+#    #+#             */
/*   Updated: 2023/07/06 15:50:04 by aderouba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt/app/app_bonus.h"

#include <math.h>

#include "minirt/app/utils/geometry/geometry_bonus.h"

t_vec2	get_sphere_pixel_pos(
					t_sphere const *sphere,
					t_ray const *normal)
{
	float	tmp_x;
	float	tmp_y;
	t_vec3	intersection_point;
	t_vec2	pixel;

	intersection_point = normal->pos;
	vec3_substract(&intersection_point, &sphere->pos);
	tmp_x = atan2f(intersection_point.x, intersection_point.z) / (2.0f * g_pi);
	tmp_y = acos(intersection_point.y / vec3_norm(&intersection_point));
	pixel.x = 1.0f - (tmp_x + 0.5f);
	pixel.y = 1.0f - (tmp_y / g_pi);
	return (pixel);
}
