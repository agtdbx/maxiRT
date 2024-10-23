/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_spotlight.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouba <aderouba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 16:38:48 by tdubois           #+#    #+#             */
/*   Updated: 2023/07/23 15:38:56 by aderouba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt/parser/parser.h"

#include <stdio.h>
#include <stddef.h>

#include "libft/libft.h"

#include "minirt/app/scene/scene.h"

t_error	parse_spotlight(
			t_parser_state *state)
{
	t_light	light;
	t_light	*new_light;

	ft_bzero(&light, sizeof(light));
	if (parse_field(state, &g_position, &light.pos) == FAILURE
		|| parse_field(state, &g_brightness, &light.brightness) == FAILURE
		|| parse_field(state, &g_color, &light.color) == FAILURE)
		return (FAILURE);
	new_light = ft_memdup(&light, sizeof(t_light));
	if (new_light == NULL)
	{
		perror("Error\nFatal");
		return (FAILURE);
	}
	new_light->next = state->scene->spotlights;
	state->scene->spotlights = new_light;
	return (SUCCESS);
}
