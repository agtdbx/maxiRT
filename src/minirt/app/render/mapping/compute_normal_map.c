/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compute_normal_map.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouba <aderouba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 16:35:34 by aderouba          #+#    #+#             */
/*   Updated: 2023/06/23 13:31:32 by aderouba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt/app/app.h"

#include "minirt/app/utils/geometry/geometry.h"

static void	compute_normal_base_sphere(t_vec3 normal_base[3]);
static void	compute_normal_base_plane(t_vec3 normal_base[3]);
static void	compute_normal_base_cylinder(
				t_vec3 normal_base[3],
				t_cylinder const *cylinder,
				t_intersect_info const *intersect_info);

void	compute_normal_map(
					t_object const *intersected_object,
					t_intersect_info const *intersect_info,
					t_vec2 const *pixel_pos,
					t_ray *normal)
{
	t_vec3	normal_base[3];

	if (intersected_object->normal_map == NULL)
		return ;
	normal_base[2] = normal->vec;
	if (intersected_object->type == OBJ_SPHERE)
		compute_normal_base_sphere(normal_base);
	else if (intersected_object->type == OBJ_PLANE)
		compute_normal_base_plane(normal_base);
	else if (intersected_object->type == OBJ_CYLINDER)
		compute_normal_base_cylinder(normal_base,
			&intersected_object->value.as_cylinder, intersect_info);
	else
	{
		normal_base[0] = (t_vec3){1.0f, 0.0f, 0.0f};
		normal_base[1] = (t_vec3){0.0f, 1.0f, 0.0f};
		normal_base[2] = (t_vec3){0.0f, 0.0f, 1.0f};
	}
	apply_normal_map(intersected_object->normal_map, pixel_pos, normal);
	normal->vec.x = (normal->vec.x * 2.0f) - 1.0f;
	normal->vec.y = (normal->vec.y * 2.0f) - 1.0f;
	normal->vec.z = (normal->vec.z * 2.0f) - 1.0f;
	normal->vec = mat_product(&normal_base[0],
							&normal_base[1], &normal_base[2], &normal->vec);
	vec3_normalize(&normal->vec);
}

static void	compute_normal_base_sphere(t_vec3 normal_base[3])
{
	normal_base[1] = (t_vec3){0.0f, 1.0f, 0.0f};
	vec3_cross(&normal_base[2], &normal_base[1], &normal_base[0]);
	vec3_normalize(&normal_base[0]);
}

static void	compute_normal_base_plane(t_vec3 normal_base[3])
{
	if (normal_base[2].x != 0.0f || normal_base[2].y != 0.0f)
		normal_base[1] = (t_vec3){-normal_base[2].y, normal_base[2].x, 0.0f};
	else
		normal_base[1] = (t_vec3){0.0f, 1.0f, 0.0f};
	vec3_cross(&normal_base[2], &normal_base[1], &normal_base[0]);
	vec3_normalize(&normal_base[0]);
	vec3_normalize(&normal_base[1]);
}

static void	compute_normal_base_cylinder(
				t_vec3 normal_base[3],
				t_cylinder const *cylinder,
				t_intersect_info const *intersect_info)
{
	if (intersect_info->sub_part_id != 0)
		compute_normal_base_plane(normal_base);
	else
	{
		vec3_normalize(&normal_base[0]);
		vec3_scale(&normal_base[0], -1.0f);
		normal_base[1] = cylinder->axis;
		vec3_scale(&normal_base[1], -1.0f);
	}
}
