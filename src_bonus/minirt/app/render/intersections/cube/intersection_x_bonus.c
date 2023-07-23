/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection_x.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouba <aderouba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 18:23:37 by aderouba          #+#    #+#             */
/*   Updated: 2023/07/20 18:28:23 by aderouba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt/app/app_bonus.h"

#include <stdbool.h>
#include <math.h>

#include "minirt/app/utils/geometry/geometry_bonus.h"

bool	intersection_with_right(
			t_ray const *ray,
			t_cube const *cube,
			t_intersect_info *intersect_info)
{
	t_intersect_info	test;
	t_vec3				p;
	t_vec2				pixel_pos;

	if (test_intersection_with_plane(ray, &cube->right, &test))
	{
		p = ray->pos;
		vec3_linear_transform(&p, test.distance, &ray->vec);
		vec3_substract(&p, &cube->right.pos);
		pixel_pos.x = vec3_dot(&cube->z_axis, &p);
		if (pixel_pos.x < -cube->half_depth || cube->half_depth < pixel_pos.x)
			return (false);
		pixel_pos.y = vec3_dot(&cube->y_axis, &p);
		if (pixel_pos.y < -cube->half_height || cube->half_height < pixel_pos.y)
			return (false);
		if (intersect_info->sub_part_id == -1
			|| test.distance < intersect_info->distance)
		{
			intersect_info->distance = test.distance;
			intersect_info->sub_part_id = 0;
			return (true);
		}
	}
	return (false);
}

bool	intersection_with_left(
			t_ray const *ray,
			t_cube const *cube,
			t_intersect_info *intersect_info)
{
	t_intersect_info	test;
	t_vec3				p;
	t_vec2				pixel_pos;

	if (test_intersection_with_plane(ray, &cube->left, &test))
	{
		p = ray->pos;
		vec3_linear_transform(&p, test.distance, &ray->vec);
		vec3_substract(&p, &cube->left.pos);
		pixel_pos.x = vec3_dot(&cube->z_axis, &p);
		if (pixel_pos.x < -cube->half_depth || cube->half_depth < pixel_pos.x)
			return (false);
		pixel_pos.y = vec3_dot(&cube->y_axis, &p);
		if (pixel_pos.y < -cube->half_height || cube->half_height < pixel_pos.y)
			return (false);
		if (intersect_info->sub_part_id == -1
			|| test.distance < intersect_info->distance)
		{
			intersect_info->distance = test.distance;
			intersect_info->sub_part_id = 1;
			return (true);
		}
	}
	return (false);
}
