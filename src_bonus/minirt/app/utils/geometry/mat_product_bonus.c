/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mat_product.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouba <aderouba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 17:24:27 by aderouba          #+#    #+#             */
/*   Updated: 2023/06/21 17:25:04 by aderouba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt/app/utils/geometry/geometry_bonus.h"

t_vec3	mat_product(
			t_vec3 const *mat_1,
			t_vec3 const *mat_2,
			t_vec3 const *mat_3,
			t_vec3 const *lambda)
{
	t_vec3	result;

	result.x = 0.0f
		+ mat_1->x * lambda->x
		+ mat_2->x * lambda->y
		+ mat_3->x * lambda->z;
	result.y = 0.0f
		+ mat_1->y * lambda->x
		+ mat_2->y * lambda->y
		+ mat_3->y * lambda->z;
	result.z = 0.0f
		+ mat_1->z * lambda->x
		+ mat_2->z * lambda->y
		+ mat_3->z * lambda->z;
	return (result);
}
