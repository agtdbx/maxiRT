/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_directive.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdubois <tdubois@student.42angouleme.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 13:39:37 by tdubois           #+#    #+#             */
/*   Updated: 2023/04/26 16:34:14 by tdubois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt/parser/parser.h"
#include "minirt/parser/parser_int.h"

#include <stdio.h>

//############################################################################//
//#### DECLARATIONS ##########################################################//

t_error			parse_directive(
					t_parser_state *state);

static t_error	_use_associated_parser(
					t_parser_state *state,
					char const *identifier);

//############################################################################//
//#### DEFINITIONS ###########################################################//

t_error	parse_directive(
					t_parser_state *state)
{
	t_error			err;
	char			*line_cpy;
	char			*identifier;

	line_cpy = ft_strdup(state->line);
	if (line_cpy == NULL)
	{
		perror("Error\nfatal");
		return (FAILURE);
	}
	state->line_cpy = line_cpy;
	identifier = ft_strtok(line_cpy, " ");
	err = _use_associated_parser(state, identifier);
	ft_memdel(&line_cpy);
	return (err);
}

static t_error	_use_associated_parser(
					t_parser_state *state,
					char const *identifier)
{
	register size_t	i;

	i = 0;
	while (i < sizeof(g_directives) / sizeof(*g_directives))
	{
		if (ft_strcmp(g_directives[i].identifier, identifier) == 0)
		{
			state->directive = &g_directives[i];
			return (g_directives[i].callback(state));
		}
		i++;
	}
	put_directive_error(state, identifier, "Unknown directive");
	return (FAILURE);
}
