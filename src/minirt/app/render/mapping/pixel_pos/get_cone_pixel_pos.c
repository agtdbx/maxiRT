/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cone_pixel_pos.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouba <aderouba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 15:49:16 by aderouba          #+#    #+#             */
/*   Updated: 2023/07/06 16:38:59 by aderouba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt/app/app.h"

#include <math.h>

#include "minirt/app/utils/geometry/geometry.h"

static float	get_height_on_cone(
					t_cone const *cone,
					t_ray const *ray,
					t_intersect_info const *intersect_info);
static void		compute_base_axis(
					t_cone const *cone,
					t_ray const *normal,
					t_vec3 *ref,
					t_vec3 *proj);

t_vec2	get_cone_pixel_pos(
					t_cone const *cone,
					t_ray const *ray,
					t_ray const *normal,
					t_intersect_info const *intersect_info)
{
	t_vec2	pixel;
	float	heigth_on_cone;
	t_vec3	ref;
	t_vec3	tmp;
	t_vec3	proj;

	if (intersect_info->sub_part_id == 1)
		return (get_plane_pixel_pos(&cone->end, normal));
	heigth_on_cone = get_height_on_cone(cone, ray, intersect_info);
	compute_base_axis(cone, normal, &ref, &proj);
	pixel.x = acosf(vec3_dot(&proj, &ref));
	pixel.x /= 2.0f * g_pi;
	vec3_cross(&cone->axis, &ref, &tmp);
	vec3_normalize(&tmp);
	if (vec3_dot(&proj, &tmp) < 0.0f)
		pixel.x = 1.0f - pixel.x;
	pixel.y = heigth_on_cone / cone->height;
	return (pixel);
}

static float	get_height_on_cone(
					t_cone const *cone,
					t_ray const *ray,
					t_intersect_info const *intersect_info)
{
	t_vec3	vec;
	float	dot[2];
	float	heigth_on_cone;

	vec3_substract_into(&vec, &ray->pos, &cone->pos);
	dot[0] = vec3_dot(&ray->vec, &cone->axis);
	dot[1] = vec3_dot(&vec, &cone->axis);
	heigth_on_cone = dot[0] * intersect_info->distance + dot[1];
	return (heigth_on_cone);
}

static void	compute_base_axis(
				t_cone const *cone,
				t_ray const *normal,
				t_vec3 *ref,
				t_vec3 *proj)
{
	t_vec3	p;
	t_vec3	tmp;

	p = normal->pos;
	vec3_substract(&p, &cone->pos);
	if (cone->axis.x != 0.0f || cone->axis.y != 0.0f)
		*ref = (t_vec3){-cone->axis.y, cone->axis.x, 0.0f};
	else
		*ref = (t_vec3){0.0f, 0.0f, 1.0f};
	vec3_cross(&cone->axis, &p, &tmp);
	vec3_cross(&cone->axis, &tmp, proj);
	vec3_normalize(ref);
	vec3_normalize(proj);
}
