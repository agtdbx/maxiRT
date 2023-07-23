/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compute_normal_ray.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouba <aderouba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 17:39:25 by tdubois           #+#    #+#             */
/*   Updated: 2023/07/05 20:41:31 by aderouba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt/app/app_bonus.h"

#include "minirt/app/scene/scene_bonus.h"
#include "minirt/app/utils/geometry/geometry_bonus.h"

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
	else if (object->type == OBJ_CONE)
		compute_normal_ray_on_cone(object, ray, intersect_info, normal);
	else if (object->type == OBJ_CUBE)
		compute_normal_ray_on_cube(object, ray, intersect_info, normal);
	else
		*normal = (t_ray){0};
}
