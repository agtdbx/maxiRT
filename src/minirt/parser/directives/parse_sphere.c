/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_sphere.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdubois <tdubois@student.42angouleme.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 16:38:48 by tdubois           #+#    #+#             */
/*   Updated: 2023/06/09 15:31:12 by tdubois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt/parser/parser.h"

#include <stdio.h>

#include "libft/libft.h"

#include "minirt/app/scene/scene.h"

t_error	parse_sphere(
			t_parser_state *state)
{
	t_sphere	sphere;

	ft_bzero(&sphere, sizeof(sphere));
	if (parse_field(state, &g_position, &sphere.pos) == FAILURE
		|| parse_field(state, &g_diameter, &sphere.diameter) == FAILURE
		|| parse_field(state, &g_color, &sphere.color) == FAILURE)
		return (FAILURE);
	return (scene_add_object(state->scene, OBJ_SPHERE, &sphere));
}
