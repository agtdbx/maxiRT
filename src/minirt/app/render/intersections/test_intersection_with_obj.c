/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_intersection_with_obj.c                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auguste <auguste@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 15:34:00 by tdubois           #+#    #+#             */
/*   Updated: 2024/03/16 19:55:50 by auguste          ###   ########.fr       */
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
	else if (object->type == OBJ_CONE)
		return (test_intersection_with_cone(
				ray, &object->value.as_cone, intersect_info));
	else if (object->type == OBJ_CUBE)
		return (test_intersection_with_cube(
				ray, &object->value.as_cube, intersect_info));
	else if (object->type == OBJ_TRIANGLE)
		return (test_intersection_with_triangle(
				ray, &object->value.as_triangle, intersect_info));
	else if (object->type == OBJ_OBJECT_FILE)
		return (test_intersection_with_object_file(
				ray, &object->value.as_object_file, intersect_info));
	else if (object->type == OBJ_PARABOLOID)
		return (test_intersection_with_paraboloid(
				ray, &object->value.as_paraboloid, intersect_info));
	return (false);
}

bool	test_intersection_with_obj_from_inside(
			t_ray const *ray,
			t_object const *object,
			t_intersect_info *intersect_info)
{
	if (object->type == OBJ_SPHERE)
		return (test_intersection_with_sphere_from_inside(
				ray, &object->value.as_sphere, intersect_info));
	else if (object->type == OBJ_CYLINDER)
		return (test_intersection_with_cylinder_from_inside(
				ray, &object->value.as_cylinder, intersect_info));
	else if (object->type == OBJ_CONE)
		return (test_intersection_with_cone_from_inside(
				ray, &object->value.as_cone, intersect_info));
	else if (object->type == OBJ_CUBE)
		return (test_intersection_with_cube_from_inside(
				ray, &object->value.as_cube, intersect_info));
	else if (object->type == OBJ_OBJECT_FILE)
		return (test_intersection_with_object_file_from_inside(
				ray, &object->value.as_object_file, intersect_info));

	return (false);
}
