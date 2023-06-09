/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_ray_on_object.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdubois <tdubois@student.42angouleme.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 13:39:22 by tdubois           #+#    #+#             */
/*   Updated: 2023/06/09 15:58:51 by tdubois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt/app/app.h"

#include <stdint.h>

#include "minirt/app/app_config.h"
#include "minirt/app/utils/color/color.h"

int32_t	render_ray_on_object(
			t_scene const *scene,
			t_object const	*intersected_object,
			t_ray const *ray,
			float distance)
{
	if (intersected_object->type == OBJ_SPHERE)
		return (render_ray_on_sphere(
				scene, (t_sphere*)&intersected_object->value, ray, distance));
	//other object types...
	return (g_color_black);
}
