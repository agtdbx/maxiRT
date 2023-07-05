/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_intersection_with_cube.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouba <aderouba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 16:25:15 by tdubois           #+#    #+#             */
/*   Updated: 2023/07/04 19:35:27 by aderouba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt/app/app.h"

#include <stdbool.h>
#include <math.h>

#include "minirt/app/utils/geometry/geometry.h"

static bool	intersection_with_right(
				t_ray const *ray,
				t_cube const *cube,
				t_intersect_info *intersect_info);
static bool	intersection_with_left(
				t_ray const *ray,
				t_cube const *cube,
				t_intersect_info *intersect_info);
static bool	intersection_with_top(
				t_ray const *ray,
				t_cube const *cube,
				t_intersect_info *intersect_info);
static bool	intersection_with_bot(
				t_ray const *ray,
				t_cube const *cube,
				t_intersect_info *intersect_info);
static bool	intersection_with_front(
				t_ray const *ray,
				t_cube const *cube,
				t_intersect_info *intersect_info);
static bool	intersection_with_back(
				t_ray const *ray,
				t_cube const *cube,
				t_intersect_info *intersect_info);

// TODO commentaire a changer
/**
 * Test ray-cylinder intersection. Algorithm is derived from
 * https://en.wikipedia.org/wiki/Line%E2%80%93cylinder_intersection
 *
 * @param[in] ray Normalized ray
 * @param[in] cylinder
 * @param[out] distance From ray origin to intersection point
 * @returns Wether ray intersects with cylinder
 */
bool	test_intersection_with_cube(
			t_ray const *ray,
			t_cube const *cube,
			t_intersect_info *intersect_info)
{
	bool				is_face_intersect;
	t_intersect_info	test;

	test.distance = 0.0f;
	test.sub_part_id = -1;
	is_face_intersect = false;
	is_face_intersect += intersection_with_right(ray, cube, &test);
	is_face_intersect += intersection_with_left(ray, cube, &test);
	is_face_intersect += intersection_with_top(ray, cube, &test);
	is_face_intersect += intersection_with_bot(ray, cube, &test);
	is_face_intersect += intersection_with_front(ray, cube, &test);
	is_face_intersect += intersection_with_back(ray, cube, &test);
	if (is_face_intersect)
	{
		intersect_info->distance = test.distance;
		intersect_info->sub_part_id = test.sub_part_id;
	}
	return (is_face_intersect);
}

static bool	intersection_with_right(
				t_ray const *ray,
				t_cube const *cube,
				t_intersect_info *intersect_info)
{
	t_intersect_info	test;
	t_vec3				p;
	t_vec2				pixel_pos;

	if (test_intersection_with_plane(ray, &cube->right, &test)
		&& test.sub_part_id == 0)
	{
		// Recupere le point
		p = ray->pos;
		vec3_linear_transform(&p, test.distance, &ray->vec);
		vec3_substract(&p, &cube->right.pos);
		// Recupere les coordonee du point sur le plan
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

static bool	intersection_with_left(
				t_ray const *ray,
				t_cube const *cube,
				t_intersect_info *intersect_info)
{
	t_intersect_info	test;
	t_vec3				p;
	t_vec2				pixel_pos;

	if (test_intersection_with_plane(ray, &cube->left, &test)
		&& test.sub_part_id == 0)
	{
		// Recupere le point
		p = ray->pos;
		vec3_linear_transform(&p, test.distance, &ray->vec);
		vec3_substract(&p, &cube->left.pos);
		// Recupere les coordonee du point sur le plan
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

static bool	intersection_with_top(
				t_ray const *ray,
				t_cube const *cube,
				t_intersect_info *intersect_info)
{
	t_intersect_info	test;
	t_vec3				p;
	t_vec2				pixel_pos;

	if (test_intersection_with_plane(ray, &cube->top, &test)
		&& test.sub_part_id == 0)
	{
		// Recupere le point
		p = ray->pos;
		vec3_linear_transform(&p, test.distance, &ray->vec);
		vec3_substract(&p, &cube->top.pos);
		// Recupere les coordonee du point sur le plan
		pixel_pos.x = vec3_dot(&cube->x_axis, &p);
		if (pixel_pos.x < -cube->half_witdh || cube->half_witdh < pixel_pos.x)
			return (false);
		pixel_pos.y = vec3_dot(&cube->z_axis, &p);
		if (pixel_pos.y < -cube->half_depth || cube->half_depth < pixel_pos.y)
			return (false);
		if (intersect_info->sub_part_id == -1
			|| test.distance < intersect_info->distance)
		{
			intersect_info->distance = test.distance;
			intersect_info->sub_part_id = 2;
			return (true);
		}
	}
	return (false);
}

static bool	intersection_with_bot(
				t_ray const *ray,
				t_cube const *cube,
				t_intersect_info *intersect_info)
{
	t_intersect_info	test;
	t_vec3				p;
	t_vec2				pixel_pos;

	if (test_intersection_with_plane(ray, &cube->bot, &test)
		&& test.sub_part_id == 0)
	{
		// Recupere le point
		p = ray->pos;
		vec3_linear_transform(&p, test.distance, &ray->vec);
		vec3_substract(&p, &cube->bot.pos);
		// Recupere les coordonee du point sur le plan
		pixel_pos.x = vec3_dot(&cube->x_axis, &p);
		if (pixel_pos.x < -cube->half_witdh || cube->half_witdh < pixel_pos.x)
			return (false);
		pixel_pos.y = vec3_dot(&cube->z_axis, &p);
		if (pixel_pos.y < -cube->half_depth || cube->half_depth < pixel_pos.y)
			return (false);
		if (intersect_info->sub_part_id == -1
			|| test.distance < intersect_info->distance)
		{
			intersect_info->distance = test.distance;
			intersect_info->sub_part_id = 3;
			return (true);
		}
	}
	return (false);
}

static bool	intersection_with_front(
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
		// Recupere le point
		p = ray->pos;
		vec3_linear_transform(&p, test.distance, &ray->vec);
		vec3_substract(&p, &cube->front.pos);
		// Recupere les coordonee du point sur le plan
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

static bool	intersection_with_back(
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
		// Recupere le point
		p = ray->pos;
		vec3_linear_transform(&p, test.distance, &ray->vec);
		vec3_substract(&p, &cube->back.pos);
		// Recupere les coordonee du point sur le plan
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
