/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_intersection_with_cylinder.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouba <aderouba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 16:25:15 by tdubois           #+#    #+#             */
/*   Updated: 2023/07/06 18:20:33 by aderouba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt/app/app.h"

#include <stdbool.h>
#include <math.h>

#include "minirt/app/utils/geometry/geometry.h"

static bool	_test_intersection_with_cylinder_bot(
				t_ray const *ray,
				t_cylinder const *cylinder,
				t_intersect_info *intersect_info);
static bool	_test_intersection_with_cylinder_top(
				t_ray const *ray,
				t_cylinder const *cylinder,
				t_intersect_info *intersect_info);
static void	_test_intersection_with_cylinder_ends(
				t_ray const *ray,
				t_cylinder const *cylinder,
				t_intersect_info *intersect_info);

/**
 * Test ray-cylinder intersection. Algorithm is derived from
 * https://hugi.scene.org/online/hugi24/
 * coding%20graphics%20chris%20dragan%20raytracing%20shapes.htm
 *
 * @param[in] ray Normalized ray
 * @param[in] cylinder
 * @param[out] distance From ray origin to intersection point
 * @returns Wether ray intersects with cylinder
 */
bool	test_intersection_with_cylinder(
			t_ray const *ray,
			t_cylinder const *cylinder,
			t_intersect_info *intersect_info)
{
	t_vec3	vec;
	float	dot[2];
	float	abc[3];
	float	discriminant;
	float	denom;
	float	heigth_on_cylinder;

	vec3_substract_into(&vec, &ray->pos, &cylinder->pos);
	dot[0] = vec3_dot(&ray->vec, &cylinder->axis);
	dot[1] = vec3_dot(&vec, &cylinder->axis);
	abc[0] = vec3_dot(&ray->vec, &ray->vec) - (dot[0] * dot[0]);
	abc[1] = (vec3_dot(&ray->vec, &vec) - (dot[0] * dot[1])) * 2.0f;
	abc[2] = vec3_dot(&vec, &vec) - (dot[1] * dot[1]) - cylinder->radius2;
	discriminant = (abc[1] * abc[1]) - (4 * abc[0] * abc[2]);
	if (discriminant < 0)
		return (false);
	else if (discriminant == 0)
	{
		intersect_info->distance = -abc[1] / (abc[0] * 2.0f);
		if (intersect_info->distance < 0.0f)
			return (false);
	}
	else
	{
		discriminant = sqrtf(discriminant);
		denom = 1.0f / (abc[0] * 2.0f);
		intersect_info->distance = (-abc[1] - discriminant) * denom;
		if (intersect_info->distance < 0.0f)
		{
			intersect_info->distance = (-abc[1] + discriminant) * denom;
			if (intersect_info->distance < 0.0f)
				return (false);
		}
	}
	heigth_on_cylinder = dot[0] * intersect_info->distance + dot[1];
	if (heigth_on_cylinder < -cylinder->half_height)
		return (_test_intersection_with_cylinder_bot(
				ray, cylinder, intersect_info));
	else if (cylinder->half_height < heigth_on_cylinder)
		return (_test_intersection_with_cylinder_top(
				ray, cylinder, intersect_info));
	intersect_info->sub_part_id = 0;
	_test_intersection_with_cylinder_ends(ray, cylinder, intersect_info);
	return (true);
}

static bool	_test_intersection_with_cylinder_bot(
				t_ray const *ray,
				t_cylinder const *cylinder,
				t_intersect_info *intersect_info)
{
	t_vec3	p;
	float	dist_on_end;

	if (test_intersection_with_plane(ray, &cylinder->bot, intersect_info)
		&& intersect_info->sub_part_id == 0)
	{
		intersect_info->sub_part_id = 1;
		p = ray->pos;
		vec3_linear_transform(&p, intersect_info->distance, &ray->vec);
		vec3_substract(&p, &cylinder->bot.pos);
		dist_on_end = vec3_dot(&p, &p);
		if (cylinder->radius2 < dist_on_end)
			return (false);
		return (true);
	}
	else if (test_intersection_with_plane(ray, &cylinder->top, intersect_info)
		&& intersect_info->sub_part_id == 0)
	{
		intersect_info->sub_part_id = 2;
		p = ray->pos;
		vec3_linear_transform(&p, intersect_info->distance, &ray->vec);
		vec3_substract(&p, &cylinder->top.pos);
		dist_on_end = vec3_dot(&p, &p);
		if (cylinder->radius2 < dist_on_end)
			return (false);
		return (true);
	}
	return (false);
}

static bool	_test_intersection_with_cylinder_top(
				t_ray const *ray,
				t_cylinder const *cylinder,
				t_intersect_info *intersect_info)
{
	t_vec3	p;
	float	dist_on_end;

	if (test_intersection_with_plane(ray, &cylinder->top, intersect_info)
		&& intersect_info->sub_part_id == 0)
	{
		intersect_info->sub_part_id = 2;
		p = ray->pos;
		vec3_linear_transform(&p, intersect_info->distance, &ray->vec);
		vec3_substract(&p, &cylinder->top.pos);
		dist_on_end = vec3_dot(&p, &p);
		if (cylinder->radius2 < dist_on_end)
			return (false);
		return (true);
	}
	else if (test_intersection_with_plane(ray, &cylinder->bot, intersect_info)
		&& intersect_info->sub_part_id == 0)
	{
		intersect_info->sub_part_id = 1;
		p = ray->pos;
		vec3_linear_transform(&p, intersect_info->distance, &ray->vec);
		vec3_substract(&p, &cylinder->bot.pos);
		dist_on_end = vec3_dot(&p, &p);
		if (cylinder->radius2 < dist_on_end)
			return (false);
		return (true);
	}
	return (false);
}

static void	_test_intersection_with_cylinder_ends(
				t_ray const *ray,
				t_cylinder const *cylinder,
				t_intersect_info *intersect_info)
{
	t_intersect_info	test;
	t_vec3				p;
	float				dist_on_end;

	if (test_intersection_with_plane(ray, &cylinder->bot, &test)
		&& test.distance <= intersect_info->distance && test.sub_part_id == 0)
	{
		p = ray->pos;
		vec3_linear_transform(&p, test.distance, &ray->vec);
		vec3_substract(&p, &cylinder->bot.pos);
		dist_on_end = vec3_dot(&p, &p);
		if (dist_on_end <= cylinder->radius2)
		{
			intersect_info->distance = test.distance;
			intersect_info->sub_part_id = 1;
		}
	}
	if (test_intersection_with_plane(ray, &cylinder->top, &test)
		&& test.distance <= intersect_info->distance && test.sub_part_id == 0)
	{
		p = ray->pos;
		vec3_linear_transform(&p, test.distance, &ray->vec);
		vec3_substract(&p, &cylinder->top.pos);
		dist_on_end = vec3_dot(&p, &p);
		if (dist_on_end <= cylinder->radius2)
		{
			intersect_info->distance = test.distance;
			intersect_info->sub_part_id = 2;
		}
	}
}
