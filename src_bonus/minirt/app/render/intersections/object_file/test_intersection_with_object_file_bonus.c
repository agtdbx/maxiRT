/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_intersection_with_object_file_bonus.c         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auguste <auguste@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 16:25:15 by tdubois           #+#    #+#             */
/*   Updated: 2024/03/17 20:04:29 by auguste          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt/app/app_bonus.h"

#include <stdbool.h>
#include <math.h>

#include "minirt/app/utils/geometry/geometry_bonus.h"


static bool	test_intersection_with_object_triangle(
			t_ray const *ray,
			t_object_triangle const *triangle,
			t_intersect_info *intersect_info);

/**
 * Test ray-object_file intersection.
 *
 * @param[in] ray Normalized ray
 * @param[in] objf The object_file to intersect
 * @param[out] distance From ray origin to intersection point
 * @returns Wether ray intersects with object_file
 */
bool	test_intersection_with_object_file(
			t_ray const *ray,
			t_object_file const *objf,
			t_intersect_info *intersect_info)
{
	t_intersect_info	intersect_test;
	t_intersect_info	local_polygon_test;
	int	i;

	if (test_intersection_with_cube(ray, &objf->bounding_box, &intersect_test))
	{
		i = 0;
		intersect_test.distance = -1.0f;
		intersect_test.sub_part_id = 0;
		while (i < objf->nb_polygons)
		{
			local_polygon_test.distance = -1.0f;
			local_polygon_test.sub_part_id = 0;
			if (objf->polygons[i].type == OBJF_TRIANGLE &&
				test_intersection_with_object_triangle(
					ray, &objf->polygons[i].value.as_objf_triangle,
					&local_polygon_test))
			{
				if (intersect_test.distance > local_polygon_test.distance
					|| intersect_test.distance == -1.0f )
				{
					intersect_test.distance = local_polygon_test.distance;
					intersect_test.sub_part_id = i;
				}
			}
			//else if (objf->polygons[i].type == OBJF_RECTANGLE &&
			//	test_intersection_with_object_rectangle(
			//		ray, &objf->polygons[i].value.as_objf_rectangle,
			//		&local_polygon_test))
			//{
			//	if (intersect_test.distance > local_polygon_test.distance
			//		|| intersect_test.distance == -1.0f )
			//	{
			//		intersect_test.distance = local_polygon_test.distance;
			//		intersect_test.sub_part_id = i;
			//	}
			//}
			i++;
		}
		if (intersect_test.distance != -1.0f)
		{
			intersect_info->distance = intersect_test.distance;
			intersect_info->sub_part_id = intersect_test.sub_part_id;
			return (true);
		}
	}
	return (false);
}


static bool	test_intersection_with_object_triangle(
			t_ray const *ray,
			t_object_triangle const *triangle,
			t_intersect_info *intersect_info)
{
	t_vec3	ray_cross_e2;
	t_vec3	s;
	t_vec3	s_cross_e1;
	float	det;
	float	inv_det;
	float	u;
	float	v;

	if (vec3_dot(&ray->vec, &triangle->normal) > 0.0f)
		return (false);

	vec3_cross(&ray->vec, &triangle->edge2, &ray_cross_e2);
	det = vec3_dot(&triangle->edge1, &ray_cross_e2);

	if (det > -0.000001f && det < 0.000001f)
		return (false); // The ray is parallel to triangle

	inv_det = 1.0f / det;
	vec3_substract_into(&s, &ray->pos, &triangle->point1);
	u = inv_det * vec3_dot(&s, &ray_cross_e2);

	if (u < 0 || u > 1)
		return (false);

	vec3_cross(&s, &triangle->edge1, &s_cross_e1);
	v = inv_det * vec3_dot(&ray->vec, &s_cross_e1);

	if (v < 0 || u + v > 1)
		return (false);

	// Now we now that we hit the triange, so go get the distance
	intersect_info->distance = inv_det * vec3_dot(&triangle->edge2, &s_cross_e1);

	if (intersect_info->distance < 0.000001f)
		return (false);

	intersect_info->sub_part_id = 0;
	return (true);
}
