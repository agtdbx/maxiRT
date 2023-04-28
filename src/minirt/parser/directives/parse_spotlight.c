/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_spotlight.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdubois <tdubois@student.42angouleme.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 16:38:48 by tdubois           #+#    #+#             */
/*   Updated: 2023/04/28 17:26:30 by tdubois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt/parser/parser.h"

#include "libft/libft.h"

#include <stdio.h>

t_error	parse_spotlight(
			t_parser_state *state)
{
	t_light	light;

	if (state->scene->spotlights != NULL)
	{
		put_directive_error(state, NULL, "More than one L directive");
		return (FAILURE);
	}
	ft_bzero(&light, sizeof(light));
	if (parse_field(state, &g_position, &light.pos) == FAILURE
		|| parse_field(state, &g_brightness, &light.brightness) == FAILURE
		|| parse_field(state, &g_color, &light.color) == FAILURE)
		return (FAILURE);
	state->scene->spotlights = ft_memdup(&light, sizeof(t_light));
	if (state->scene->spotlights == NULL)
	{
		perror("Error\nFatal");
		return (FAILURE);
	}
	return (SUCCESS);
}
