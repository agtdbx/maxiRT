/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_camera.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdubois <tdubois@student.42angouleme.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 16:38:48 by tdubois           #+#    #+#             */
/*   Updated: 2023/06/09 15:30:26 by tdubois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt/parser/parser_bonus.h"

#include <stdio.h>
#include <stddef.h>

#include "libft/libft.h"

#include "minirt/app/scene/scene_bonus.h"

t_error	parse_camera(
			t_parser_state *state)
{
	t_camera	camera;

	if (state->scene->camera != NULL)
	{
		put_directive_error(state, NULL, "More than one C directive");
		return (FAILURE);
	}
	ft_bzero(&camera, sizeof(camera));
	if (parse_field(state, &g_position, &camera.pos) == FAILURE
		|| parse_field(state, &g_direction, &camera.direction) == FAILURE
		|| parse_field(state, &g_fov, &camera.fov) == FAILURE)
		return (FAILURE);
	state->scene->camera = ft_memdup(&camera, sizeof(t_camera));
	if (state->scene->camera == NULL)
	{
		perror("Error\nFatal");
		return (FAILURE);
	}
	return (SUCCESS);
}
