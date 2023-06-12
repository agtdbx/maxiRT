/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_intersection_with_obj.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdubois <tdubois@student.42angouleme.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 15:34:00 by tdubois           #+#    #+#             */
/*   Updated: 2023/06/12 15:35:07 by tdubois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt/app/app.h"

#include <stdbool.h>

bool	test_intersection_with_obj(
			t_ray const *ray,
			t_object const *object,
			float *distance)
{
	if (object->type == OBJ_SPHERE)
		return (test_intersection_with_sphere(
					ray, &object->value.as_sphere, distance));
	return (false);
}
