/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_directive.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdubois <tdubois@student.42angouleme.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 13:39:37 by tdubois           #+#    #+#             */
/*   Updated: 2023/04/28 15:16:45 by tdubois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt/parser/parser.h"

#include <stdio.h>
#include <stdbool.h>

//############################################################################//
//#### DECLARATIONS ##########################################################//

t_error			parse_directive(
					t_parser_state *state);

static t_error	_use_associated_parser(
					t_parser_state *state,
					char const *identifier);

static bool		_has_any_field_left(
					t_parser_state *state);

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
			if (g_directives[i].callback(state) == FAILURE)
				return (FAILURE);
			if (_has_any_field_left(state))
				return (FAILURE);
			return (SUCCESS);
		}
		++i;
	}
	put_unknown_directive_error(state, identifier);
	return (FAILURE);
}

static bool	_has_any_field_left(
				t_parser_state *state)
{
	char *const	tok = ft_strtok(NULL, " ");

	if (tok != NULL)
	{
		put_directive_error(state, tok, "Unexpected field");
		return (true);
	}
	return (false);
}
