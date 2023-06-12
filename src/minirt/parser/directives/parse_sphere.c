/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_sphere.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdubois <tdubois@student.42angouleme.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 16:38:48 by tdubois           #+#    #+#             */
/*   Updated: 2023/06/12 17:33:14 by tdubois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt/parser/parser.h"

#include <stdio.h>

#include "libft/libft.h"

#include "minirt/app/scene/scene.h"
#include "minirt/app/app_config.h"

t_error	parse_sphere(
			t_parser_state *state)
{
	t_object	sphere;
	t_sphere	*const geometry = &sphere.value.as_sphere;

	ft_bzero(&sphere, sizeof(sphere));
	if (parse_field(state, &g_position, &geometry->pos) == FAILURE
		|| parse_field(state, &g_diameter, &geometry->diameter) == FAILURE
		|| parse_field(state, &g_color, &sphere.color) == FAILURE)
		return (FAILURE);
	sphere.type = OBJ_SPHERE;
	sphere.opacity = g_sphere_default_opacity;
	sphere.refraction_ratio = g_sphere_default_refraction_ratio;
	sphere.reflection_ratio = g_sphere_default_reflection_ratio;
	return (scene_add_object(state->scene, &sphere));
}
