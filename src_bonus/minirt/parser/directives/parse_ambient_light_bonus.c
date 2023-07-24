/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_ambient_light.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdubois <tdubois@student.42angouleme.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 16:38:48 by tdubois           #+#    #+#             */
/*   Updated: 2023/06/09 15:29:40 by tdubois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt/parser/parser_bonus.h"

#include <stdio.h>
#include <stddef.h>

#include "libft/libft.h"

#include "minirt/app/scene/scene_bonus.h"

t_error	parse_ambient_light(
			t_parser_state *state)
{
	t_light	light;

	if (state->scene->ambient_lightning != NULL)
	{
		put_directive_error(state, NULL, "More than one A directive");
		return (FAILURE);
	}
	ft_bzero(&light, sizeof(light));
	if (parse_field(state, &g_brightness, &light.brightness) == FAILURE
		|| parse_field(state, &g_color, &light.color) == FAILURE)
		return (FAILURE);
	state->scene->ambient_lightning = ft_memdup(&light, sizeof(t_light));
	if (state->scene->ambient_lightning == NULL)
	{
		perror("Error\nFatal");
		return (FAILURE);
	}
	return (SUCCESS);
}
