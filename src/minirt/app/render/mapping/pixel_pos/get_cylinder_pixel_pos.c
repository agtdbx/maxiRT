/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cylinder_pixel_pos.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouba <aderouba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 15:49:05 by aderouba          #+#    #+#             */
/*   Updated: 2023/07/06 16:34:47 by aderouba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt/app/app.h"

#include <math.h>

#include "minirt/app/utils/geometry/geometry.h"

static float	get_height_on_cylinder(
					t_cylinder const *cylinder,
					t_ray const *ray,
					t_intersect_info const *intersect_info);
static void		compute_base_axis(
					t_cylinder const *cylinder,
					t_ray const *normal,
					t_vec3 *ref,
					t_vec3 *proj);

t_vec2	get_cylinder_pixel_pos(
					t_cylinder const *cylinder,
					t_ray const *ray,
					t_ray const *normal,
					t_intersect_info const *intersect_info)
{
	t_vec2	pixel;
	float	heigth_on_cylinder;
	t_vec3	ref;
	t_vec3	tmp;
	t_vec3	proj;

	if (intersect_info->sub_part_id == 1)
		return (get_plane_pixel_pos(&cylinder->bot, normal));
	else if (intersect_info->sub_part_id == 2)
		return (get_plane_pixel_pos(&cylinder->top, normal));
	heigth_on_cylinder = get_height_on_cylinder(cylinder, ray, intersect_info);
	compute_base_axis(cylinder, normal, &ref, &proj);
	pixel.x = acosf(vec3_dot(&proj, &ref));
	pixel.x /= 2.0f * g_pi;
	vec3_cross(&cylinder->axis, &ref, &tmp);
	vec3_normalize(&tmp);
	if (vec3_dot(&proj, &tmp) < 0.0f)
		pixel.x = 1.0f - pixel.x;
	pixel.y = (heigth_on_cylinder + cylinder->half_height) / cylinder->height;
	return (pixel);
}

static float	get_height_on_cylinder(
					t_cylinder const *cylinder,
					t_ray const *ray,
					t_intersect_info const *intersect_info)
{
	t_vec3	vec;
	float	dot[2];
	float	heigth_on_cylinder;

	vec3_substract_into(&vec, &ray->pos, &cylinder->pos);
	dot[0] = vec3_dot(&ray->vec, &cylinder->axis);
	dot[1] = vec3_dot(&vec, &cylinder->axis);
	heigth_on_cylinder = dot[0] * intersect_info->distance + dot[1];
	return (heigth_on_cylinder);
}

static void	compute_base_axis(
				t_cylinder const *cylinder,
				t_ray const *normal,
				t_vec3 *ref,
				t_vec3 *proj)
{
	t_vec3	p;
	t_vec3	tmp;

	p = normal->pos;
	vec3_substract(&p, &cylinder->pos);
	if (cylinder->axis.x != 0.0f || cylinder->axis.y != 0.0f)
		*ref = (t_vec3){-cylinder->axis.y, cylinder->axis.x, 0.0f};
	else
		*ref = (t_vec3){0.0f, 0.0f, 1.0f};
	vec3_cross(&cylinder->axis, &p, &tmp);
	vec3_cross(&cylinder->axis, &tmp, proj);
	vec3_normalize(ref);
	vec3_normalize(proj);
}
