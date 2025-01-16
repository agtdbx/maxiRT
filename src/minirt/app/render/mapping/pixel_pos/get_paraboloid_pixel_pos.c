/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_paraboloid_pixel_pos.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damien <damien@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 12:07:26 by damien            #+#    #+#             */
/*   Updated: 2025/01/16 23:29:02 by damien           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt/app/app.h"

#include <math.h>

#include "minirt/app/utils/geometry/geometry.h"

static void compute_base_axis(
					t_paraboloid const *paraboloid,
					t_ray const *normal,
					t_vec3 *ref,
					t_vec3 *proj);

t_vec2	get_paraboloid_pixel_pos(
				t_paraboloid const *paraboloid,
				t_ray const *ray,
				t_ray const *normal,
				t_intersect_info const *intersect_info)
{
	t_vec3	ref;
	t_vec3	proj;
	t_vec3	local;
	t_vec3	vec;
	t_vec2	pixel;
	t_vec3 tmp;
	vec3_substract(&local, &paraboloid->pos);
	compute_base_axis(paraboloid, normal, &ref, &proj);
	t_vec3 p = ray->pos;
	vec3_linear_transform(&p, intersect_info->distance, &ray->vec);
	vec3_substract_into(&vec, &p, &paraboloid->pos);
	float height_on_para = vec3_dot(&vec, &paraboloid->dir);
	pixel.x = acosf(vec3_dot(&proj, &ref));
	pixel.x /= 2.0f * g_pi;
	vec3_cross(&paraboloid->dir, &ref, &tmp);
	vec3_normalize(&tmp);
	if (vec3_dot(&proj, &tmp) < 0.0f)
		pixel.x = 1.0f - pixel.x;
	pixel.y = height_on_para / paraboloid->k;
	return (pixel);
}

static void	compute_base_axis(
					t_paraboloid const *paraboloid,
					t_ray const *normal,
					t_vec3 *ref,
					t_vec3 *proj)
{
	t_vec3	p;
	t_vec3	tmp;

	p = normal->pos;
	vec3_substract(&p, &paraboloid->pos);
	if (paraboloid->dir.x != 0.0f || paraboloid->dir.y != 0.0f)
		*ref = (t_vec3){-paraboloid->dir.y, paraboloid->dir.x, 0.0f};
	else 	
		*ref = (t_vec3){0.0f, 0.0f, 1.0f};
	vec3_cross(&paraboloid->dir, &p, &tmp);
	vec3_cross(&paraboloid->dir, &tmp, proj);
	vec3_normalize(ref);
	vec3_normalize(proj);
}
