/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_triangle_pixel_pos_bonus.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auguste <auguste@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 15:48:59 by aderouba          #+#    #+#             */
/*   Updated: 2024/03/11 16:00:49 by auguste          ###   ########.fr       */
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

	(void)triangle;
	(void)normal;
	pixel.x = 0.0f;
	pixel.y = 0.0f;
	return (pixel);
}
