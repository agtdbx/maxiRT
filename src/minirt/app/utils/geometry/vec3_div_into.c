/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_div.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damien <damien@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 22:17:38 by damien            #+#    #+#             */
/*   Updated: 2025/01/17 22:19:55 by damien           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt/app/utils/geometry/geometry.h"

void	vec3_div_into(
			t_vec3 *lhs,
			t_vec3 *rhs,
			t_vec3 *res)
{
	res->x = lhs->x / rhs->x;
	res->y = lhs->y / rhs->y;
	res->z = lhs->z / rhs->z;
}
