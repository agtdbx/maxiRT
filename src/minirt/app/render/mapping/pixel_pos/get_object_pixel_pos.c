/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_object_pixel_pos.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auguste <auguste@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 11:58:24 by aderouba          #+#    #+#             */
/*   Updated: 2024/03/17 12:22:46 by auguste          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt/app/app.h"

#include <math.h>

#include "minirt/app/utils/geometry/geometry.h"

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
	t_vec2	pixel_pos;

	if (object->type == OBJ_SPHERE)
		pixel_pos = get_sphere_pixel_pos(&object->value.as_sphere, normal);
	else if (object->type == OBJ_PLANE)
		pixel_pos = get_plane_pixel_pos(&object->value.as_plane, normal);
	else if (object->type == OBJ_CYLINDER)
		pixel_pos = get_cylinder_pixel_pos(
				&object->value.as_cylinder, ray, normal, intersect_info);
	else if (object->type == OBJ_CONE)
		pixel_pos = get_cone_pixel_pos(
				&object->value.as_cone, ray, normal, intersect_info);
	else if (object->type == OBJ_CUBE)
		pixel_pos = get_cube_pixel_pos(
				&object->value.as_cube, normal, intersect_info);
	else if (object->type == OBJ_SKYBOX)
		pixel_pos = get_skybox_pixel_pos(
				&object->value.as_skybox, normal, intersect_info);
	else if (object->type == OBJ_TRIANGLE)
		pixel_pos = get_triangle_pixel_pos(
				&object->value.as_triangle, normal);
	else if (object->type == OBJ_OBJECT_FILE)
		pixel_pos = get_object_file_pixel_pos(
				&object->value.as_object_file, normal, intersect_info);
	else
		pixel_pos = (t_vec2){0};

	pixel_pos.x += object->texture_shift.x;
	if (pixel_pos.x > 1.0f)
		pixel_pos.x -= 1.0f;
	pixel_pos.y += object->texture_shift.y;
	if (pixel_pos.y > 1.0f)
		pixel_pos.y -= 1.0f;

	return (pixel_pos);
}
