/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compute_normal_ray.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auguste <auguste@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 17:39:25 by tdubois           #+#    #+#             */
/*   Updated: 2024/03/16 20:08:03 by auguste          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt/app/app.h"

#include "minirt/app/scene/scene.h"
#include "minirt/app/utils/geometry/geometry.h"

/**
 * @param[in] object
 * @param[in] ray
 * @param[in] distance
 * @param[out] normal
 */
void	compute_normal_ray(
			t_object const *object,
			t_ray const *ray,
			t_intersect_info const *intersect_info,
			t_ray *normal)
{
	if (object->type == OBJ_SPHERE)
		compute_normal_ray_on_sphere(
			object, ray, intersect_info->distance, normal);
	else if (object->type == OBJ_PLANE)
		compute_normal_ray_on_plane(object, ray, intersect_info, normal);
	else if (object->type == OBJ_CYLINDER)
		compute_normal_ray_on_cylinder(object, ray, intersect_info, normal);
	else if (object->type == OBJ_PARABOLOID)
		compute_normal_ray_on_paraboloid(object, ray, intersect_info, normal);
	else if (object->type == OBJ_CONE)
		compute_normal_ray_on_cone(object, ray, intersect_info, normal);
	else if (object->type == OBJ_CUBE)
		compute_normal_ray_on_cube(object, ray, intersect_info, normal);
	else if (object->type == OBJ_SKYBOX)
		compute_normal_ray_on_skybox(object, ray, intersect_info, normal);
	else if (object->type == OBJ_TRIANGLE)
		compute_normal_ray_on_triangle(object, ray, intersect_info, normal);
	else if (object->type == OBJ_OBJECT_FILE)
		compute_normal_ray_on_object_file(object, ray, intersect_info, normal);
	else
		*normal = (t_ray){0};
}
