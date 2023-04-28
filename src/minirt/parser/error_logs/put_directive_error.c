/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_directive_error.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdubois <tdubois@student.42angouleme.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 16:27:24 by tdubois           #+#    #+#             */
/*   Updated: 2023/04/28 14:53:53 by tdubois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt/parser/parser.h"

#include <stdio.h>

#define RED "\e[91m"
#define NC "\e[0m"

static const char	g_directive_error_msg[] = \
	"Error"								"\n"
	"%s:"								"\n"
	"row %03zi> %.*s" RED"%s"NC "%s"	"\n"
	"col %03ti> " RED"%s"NC ": %s"		"\n"
	"Usage: %s"							"\n";

void	put_directive_error(
				t_parser_state *state,
				char const *token,
				char const *error)
{
	if (token == NULL)
		token = state->line_cpy;
	printf(
		g_directive_error_msg,
		state->filename,
		state->line_number,
		(int)(token - state->line_cpy), state->line,
		token,
		state->line + (int)(token - state->line_cpy) + ft_strlen(token),
		token - state->line_cpy + 1, token, error,
		state->directive->usage);
}
