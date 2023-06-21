/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_object_pixel_pos.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouba <aderouba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 11:58:24 by aderouba          #+#    #+#             */
/*   Updated: 2023/06/21 16:10:59 by aderouba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt/app/app.h"

#include <math.h>

#include "minirt/app/utils/geometry/geometry.h"

#include "minirt/debug/debug.h" // TODO

static t_vec2	get_sphere_pixel_pos(
			t_object const *object,
			t_ray const *normal);

t_vec2	get_object_pixel_pos(
			t_object const *object,
			t_ray const *ray,
			t_ray const *normal)
{
	(void)ray;
	if (object->type == OBJ_SPHERE)
		return (get_sphere_pixel_pos(object, normal));
	return ((t_vec2){ 0 });
}

/**
 * Calculate the pixel position
 *
 * @param[in] object Normalized ray
 * @param[in] ray
 * @param[in] normal From ray origin to intersection point
 * @returns The pixel coordonate
 */
static t_vec2	get_sphere_pixel_pos(
			t_object const *object,
			t_ray const *normal)
{
	float	tmp_x;
	float	tmp_y;
	t_vec3	intersection_point;
	t_vec2	pixel;

	intersection_point = normal->pos;
	vec3_substract(&intersection_point, &object->value.as_sphere.pos);
	tmp_x = atan2f(intersection_point.x, intersection_point.z) / (2.0f * g_pi);
	tmp_y = acos(intersection_point.y / vec3_norm(&intersection_point));
	pixel.x = 1.0f - (tmp_x + 0.5f);
	pixel.y = 1.0f - (tmp_y / g_pi);
	DEBUG("x %f, y %f\n", pixel.x, pixel.y);
	return (pixel);
}
