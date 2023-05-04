/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdubois <tdubois@student.42angouleme.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 16:58:24 by tdubois           #+#    #+#             */
/*   Updated: 2023/05/04 17:00:33 by tdubois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt/utils/geometry.h>

extern inline t_vec3	vec3(
							float x,
							float y,
							float z)
{
	return ((t_vec3){.x = x, .y = y, .z = z});
}
