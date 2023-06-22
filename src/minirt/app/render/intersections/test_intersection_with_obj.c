/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_intersection_with_obj.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouba <aderouba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 15:34:00 by tdubois           #+#    #+#             */
/*   Updated: 2023/06/22 18:29:18 by aderouba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt/app/app.h"

#include <stdbool.h>

bool	test_intersection_with_obj(
			t_ray const *ray,
			t_object const *object,
			t_intersect_info *intersect_info)
{
	if (object->type == OBJ_SPHERE)
		return (test_intersection_with_sphere(
					ray, &object->value.as_sphere, intersect_info));
	else if (object->type == OBJ_PLANE)
		return (test_intersection_with_plane(
					ray, &object->value.as_plane, intersect_info));
	else if (object->type == OBJ_CYLINDER)
		return (test_intersection_with_cylinder(
					ray, &object->value.as_cylinder, intersect_info));
	return (false);
}
