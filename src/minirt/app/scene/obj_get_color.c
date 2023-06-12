/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_get_color.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdubois <tdubois@student.42angouleme.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 15:20:23 by tdubois           #+#    #+#             */
/*   Updated: 2023/06/12 15:20:49 by tdubois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt/app/scene/scene.h>

t_color const	*obj_get_color(
					t_object const *object)
{
	if (object->type == OBJ_SPHERE)
		return (&object->value.as_sphere.color);
	return (NULL);
}
