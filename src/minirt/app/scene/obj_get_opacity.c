/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_get_opacity.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdubois <tdubois@student.42angouleme.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 15:22:04 by tdubois           #+#    #+#             */
/*   Updated: 2023/06/12 15:22:22 by tdubois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt/app/scene/scene.h>

float	obj_get_opacity(
			t_object const *object)
{
	if (object->type == OBJ_SPHERE)
		return (object->value.as_sphere.opacity);
	return (1.0f);
}
