/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_object_pixel_pos.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouba <aderouba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 11:58:24 by aderouba          #+#    #+#             */
/*   Updated: 2023/06/22 19:07:54 by aderouba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt/app/app.h"

#include <math.h>

#include "minirt/app/utils/geometry/geometry.h"

static t_vec2	get_sphere_pixel_pos(
			t_sphere const *sphere,
			t_ray const *normal);

static t_vec2	get_plane_pixel_pos(
			t_plane const *plane,
			t_ray const *normal);

static t_vec2	get_cylinder_pixel_pos(
			t_plane const *plane,
			t_ray const *normal);

t_vec2	get_object_pixel_pos(
			t_object const *object,
			t_ray const *ray,
			t_ray const *normal)
{
	(void)ray;
	if (object->type == OBJ_SPHERE)
		return (get_sphere_pixel_pos(&object->value.as_sphere, normal));
	else if (object->type == OBJ_PLANE)
		return (get_plane_pixel_pos(&object->value.as_plane, normal));
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


static t_vec2	get_plane_pixel_pos(
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
	pixel.x = vec3_dot(&o_x, &normal->pos) / 3.0f; //TODO Pour la taille le 3.0f
	pixel.x -= (int)pixel.x;
	if (pixel.x > 0.0f)
		pixel.x = 1.0f - pixel.x;
	else
		pixel.x = fabs(pixel.x);
	pixel.y = vec3_dot(&o_y, &normal->pos) / 3.0f; //TODO Pour la taille le 3.0f
	pixel.y -= (int)pixel.y;
	if (pixel.y > 0.0f)
		pixel.y = 1.0f - pixel.y;
	else
		pixel.y = fabs(pixel.y);
	return (pixel);
}

static t_vec2	get_cylinder_pixel_pos(
			t_plane const *plane,
			t_ray const *normal)
{
	(void)plane;
	(void)normal;
	return ((t_vec2){ 0 });
}
