/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection_z.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouba <aderouba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 18:23:37 by aderouba          #+#    #+#             */
/*   Updated: 2023/07/06 18:24:58 by aderouba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt/app/app.h"

#include <stdbool.h>
#include <math.h>

#include "minirt/app/utils/geometry/geometry.h"

bool	intersection_with_front(
			t_ray const *ray,
			t_cube const *cube,
			t_intersect_info *intersect_info)
{
	t_intersect_info	test;
	t_vec3				p;
	t_vec2				pixel_pos;

	if (test_intersection_with_plane(ray, &cube->front, &test)
		&& test.sub_part_id == 0)
	{
		p = ray->pos;
		vec3_linear_transform(&p, test.distance, &ray->vec);
		vec3_substract(&p, &cube->front.pos);
		pixel_pos.x = vec3_dot(&cube->x_axis, &p);
		if (pixel_pos.x < -cube->half_witdh || cube->half_witdh < pixel_pos.x)
			return (false);
		pixel_pos.y = vec3_dot(&cube->y_axis, &p);
		if (pixel_pos.y < -cube->half_height || cube->half_height < pixel_pos.y)
			return (false);
		if (intersect_info->sub_part_id == -1
			|| test.distance < intersect_info->distance)
		{
			intersect_info->distance = test.distance;
			intersect_info->sub_part_id = 4;
			return (true);
		}
	}
	return (false);
}

bool	intersection_with_back(
			t_ray const *ray,
			t_cube const *cube,
			t_intersect_info *intersect_info)
{
	t_intersect_info	test;
	t_vec3				p;
	t_vec2				pixel_pos;

	if (test_intersection_with_plane(ray, &cube->back, &test)
		&& test.sub_part_id == 0)
	{
		p = ray->pos;
		vec3_linear_transform(&p, test.distance, &ray->vec);
		vec3_substract(&p, &cube->back.pos);
		pixel_pos.x = vec3_dot(&cube->x_axis, &p);
		if (pixel_pos.x < -cube->half_witdh || cube->half_witdh < pixel_pos.x)
			return (false);
		pixel_pos.y = vec3_dot(&cube->y_axis, &p);
		if (pixel_pos.y < -cube->half_height || cube->half_height < pixel_pos.y)
			return (false);
		if (intersect_info->sub_part_id == -1
			|| test.distance < intersect_info->distance)
		{
			intersect_info->distance = test.distance;
			intersect_info->sub_part_id = 5;
			return (true);
		}
	}
	return (false);
}
