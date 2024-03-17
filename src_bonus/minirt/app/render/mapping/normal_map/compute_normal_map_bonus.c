/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compute_normal_map_bonus.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auguste <auguste@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 16:35:34 by aderouba          #+#    #+#             */
/*   Updated: 2024/03/17 21:58:57 by auguste          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt/app/app_bonus.h"

#include "minirt/app/utils/geometry/geometry_bonus.h"

static void	compute_normal_base(
				t_object const *intersected_object,
				t_intersect_info const *intersect_info,
				t_vec3 normal_base[3]);

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
	compute_normal_base(intersected_object, intersect_info, normal_base);
	apply_normal_map(intersected_object->normal_map, pixel_pos, normal);
	normal->vec.x = (normal->vec.x * 2.0f) - 1.0f;
	normal->vec.y = (normal->vec.y * 2.0f) - 1.0f;
	normal->vec.z = (normal->vec.z * 2.0f) - 1.0f;
	normal->vec = mat_product(&normal_base[0],
			&normal_base[1], &normal_base[2], &normal->vec);
	vec3_normalize(&normal->vec);
}

static void	compute_normal_base(
				t_object const *intersected_object,
				t_intersect_info const *intersect_info,
				t_vec3 normal_base[3])
{
	if (intersected_object->type == OBJ_SPHERE)
		compute_normal_base_sphere(normal_base);
	else if (intersected_object->type == OBJ_PLANE)
		compute_normal_base_plane(normal_base);
	else if (intersected_object->type == OBJ_CYLINDER)
		compute_normal_base_cylinder(normal_base,
			&intersected_object->value.as_cylinder, intersect_info);
	else if (intersected_object->type == OBJ_CONE)
		compute_normal_base_cone(normal_base,
			&intersected_object->value.as_cone, intersect_info);
	else if (intersected_object->type == OBJ_CUBE)
		compute_normal_base_cube(normal_base,
			&intersected_object->value.as_cube, intersect_info);
	else if (intersected_object->type == OBJ_TRIANGLE)
		compute_normal_base_triangle(normal_base);
	else if (intersected_object->type == OBJ_OBJECT_FILE)
		compute_normal_base_object_file(normal_base,
			&intersected_object->value.as_object_file, intersect_info);
	else
	{
		normal_base[0] = (t_vec3){1.0f, 0.0f, 0.0f};
		normal_base[1] = (t_vec3){0.0f, 1.0f, 0.0f};
		normal_base[2] = (t_vec3){0.0f, 0.0f, 1.0f};
	}
}
