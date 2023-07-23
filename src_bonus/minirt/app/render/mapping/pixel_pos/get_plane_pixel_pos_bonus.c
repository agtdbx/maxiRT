/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_plane_pixel_pos.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouba <aderouba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 15:48:59 by aderouba          #+#    #+#             */
/*   Updated: 2023/07/06 15:51:11 by aderouba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt/app/app_bonus.h"

#include <math.h>

#include "minirt/app/utils/geometry/geometry_bonus.h"

t_vec2	get_plane_pixel_pos(
					t_plane const *plane,
					t_ray const *normal)
{
	t_vec2	pixel;
	t_vec3	o_x;
	t_vec3	o_y;

	if (plane->normal.x != 0.0f || plane->normal.y != 0.0f)
		o_y = (t_vec3){-plane->normal.y, plane->normal.x, 0.0f};
	else
		o_y = (t_vec3){0.0f, 1.0f, 0.0f};
	vec3_cross(&plane->normal, &o_y, &o_x);
	vec3_normalize(&o_x);
	vec3_normalize(&o_y);
	pixel.x = vec3_dot(&o_x, &normal->pos) / 3.0f;
	pixel.x -= (int)pixel.x;
	if (pixel.x > 0.0f)
		pixel.x = 1.0f - pixel.x;
	else
		pixel.x = fabs(pixel.x);
	pixel.y = vec3_dot(&o_y, &normal->pos) / 3.0f;
	pixel.y -= (int)pixel.y;
	if (pixel.y > 0.0f)
		pixel.y = 1.0f - pixel.y;
	else
		pixel.y = fabs(pixel.y);
	return (pixel);
}
