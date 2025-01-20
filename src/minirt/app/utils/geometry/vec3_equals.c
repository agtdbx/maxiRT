/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_equals.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damien <damien@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 22:10:08 by damien            #+#    #+#             */
/*   Updated: 2025/01/18 01:20:15 by damien           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt/app/utils/geometry/geometry.h"

#include <stdbool.h>

bool	vec3_equals(
			t_vec3 *a,
			t_vec3 *b)
{
	return (a->x == b->x && a->y == b->y && a->z == b->z);
}
