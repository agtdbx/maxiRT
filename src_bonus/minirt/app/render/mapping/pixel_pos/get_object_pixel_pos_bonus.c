/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_object_pixel_pos_bonus.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auguste <auguste@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 11:58:24 by aderouba          #+#    #+#             */
/*   Updated: 2024/03/11 16:02:07 by auguste          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt/app/app_bonus.h"

#include <math.h>

#include "minirt/app/utils/geometry/geometry_bonus.h"

/**
 * Calculate the pixel position
 *
 * @param[in] object Normalized ray
 * @param[in] ray
 * @param[in] normal From ray origin to intersection point
 * @returns The pixel coordonate
 */
t_vec2	get_object_pixel_pos(
			t_object const *object,
			t_ray const *ray,
			t_ray const *normal,
			t_intersect_info const *intersect_info)
{
	if (object->type == OBJ_SPHERE)
		return (get_sphere_pixel_pos(&object->value.as_sphere, normal));
	else if (object->type == OBJ_PLANE)
		return (get_plane_pixel_pos(&object->value.as_plane, normal));
	else if (object->type == OBJ_CYLINDER)
		return (get_cylinder_pixel_pos(
				&object->value.as_cylinder, ray, normal, intersect_info));
	else if (object->type == OBJ_CONE)
		return (get_cone_pixel_pos(
				&object->value.as_cone, ray, normal, intersect_info));
	else if (object->type == OBJ_CUBE)
		return (get_cube_pixel_pos(
				&object->value.as_cube, normal, intersect_info));
	else if (object->type == OBJ_TRIANGLE)
		return (get_triangle_pixel_pos(
				&object->value.as_triangle, normal));
	return ((t_vec2){0});
}
