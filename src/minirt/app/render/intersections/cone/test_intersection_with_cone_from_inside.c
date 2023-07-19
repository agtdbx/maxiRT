/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_intersection_with_cone_from_inside.c          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouba <aderouba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 16:25:15 by tdubois           #+#    #+#             */
/*   Updated: 2023/07/19 20:34:59 by aderouba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt/app/app.h"

#include <stdbool.h>
#include <math.h>

#include "minirt/app/utils/geometry/geometry.h"

#include "minirt/debug/debug.h"

static bool	_test_intersection_with_cone_end(
				t_ray const *ray,
				t_cone const *cone,
				t_intersect_info *intersect_info);
static void	_test_intersection_with_cone_end_if_it_closer(
				t_ray const *ray,
				t_cone const *cone,
				t_intersect_info *intersect_info);

/**
 * Test ray-cone intersection. Algorithm is derived from
 * https://hugi.scene.org/online/hugi24/
 * coding%20graphics%20chris%20dragan%20\raytracing%20shapes.htm
 *
 * @param[in] ray Normalized ray
 * @param[in] cylinder
 * @param[out] distance From ray origin to intersection point
 * @returns Wether ray intersects with cylinder
 */
bool	test_intersection_with_cone_from_inside(
			t_ray const *ray,
			t_cone const *cone,
			t_intersect_info *intersect_info)
{
	t_vec3		vec;
	float		dot[2];
	float		abc[3];
	float		heigth_on_cone;

	vec3_substract_into(&vec, &ray->pos, &cone->pos);
	dot[0] = vec3_dot(&ray->vec, &cone->axis);
	dot[1] = vec3_dot(&vec, &cone->axis);
	abc[0] = vec3_dot(&ray->vec, &ray->vec) - (cone->ratio * (dot[0] * dot[0]));
	abc[1] = (vec3_dot(&ray->vec, &vec) - cone->ratio * dot[0] * dot[1]) * 2.0f;
	abc[2] = vec3_dot(&vec, &vec) - (cone->ratio * (dot[1] * dot[1]));
	if (compute_intersection_distance_from_inside(intersect_info, abc) == false)
		return (false);
	heigth_on_cone = dot[0] * intersect_info->distance + dot[1];
	if (cone->height < heigth_on_cone)
		return (_test_intersection_with_cone_end(
				ray, cone, intersect_info));
	intersect_info->sub_part_id = 0;
	_test_intersection_with_cone_end_if_it_closer(ray, cone, intersect_info);
	if (intersect_info->sub_part_id == 0 && heigth_on_cone < 0.0f)
		return (false);
	return (true);
}

static bool	_test_intersection_with_cone_end(
				t_ray const *ray,
				t_cone const *cone,
				t_intersect_info *intersect_info)
{
	t_vec3	p;
	float	dist_on_end;

	if (test_intersection_with_plane(ray, &cone->end, intersect_info)
		&& intersect_info->sub_part_id == 1)
	{
		intersect_info->sub_part_id = 1;
		p = ray->pos;
		vec3_linear_transform(&p, intersect_info->distance, &ray->vec);
		vec3_substract(&p, &cone->end.pos);
		dist_on_end = vec3_dot(&p, &p);
		if (cone->radius2 < dist_on_end)
			return (false);
		return (true);
	}
	return (false);
}

static void	_test_intersection_with_cone_end_if_it_closer(
				t_ray const *ray,
				t_cone const *cone,
				t_intersect_info *intersect_info)
{
	t_intersect_info	test;
	t_vec3				p;
	float				dist_on_end;

	if (test_intersection_with_plane(ray, &cone->end, &test)
		&& test.distance <= intersect_info->distance && test.sub_part_id == 1)
	{
		p = ray->pos;
		vec3_linear_transform(&p, test.distance, &ray->vec);
		vec3_substract(&p, &cone->end.pos);
		dist_on_end = vec3_dot(&p, &p);
		if (dist_on_end <= cone->radius2)
		{
			intersect_info->distance = test.distance;
			intersect_info->sub_part_id = 1;
		}
	}
}
