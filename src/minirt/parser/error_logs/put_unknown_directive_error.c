/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_unknown_directive_error.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damien <damien@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 16:27:24 by tdubois           #+#    #+#             */
/*   Updated: 2024/12/12 09:34:17 by damien           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt/parser/parser.h"

#include <stdio.h>

#define RED "\e[91m"
#define NC "\e[0m"

static const char	g_directive_error_msg[] = \
	"Error"											"\n"
	"%s:"											"\n"
	"row %03zi> %.*s" RED"%s"NC "%s"				"\n"
	"col %03ti> " RED"%s"NC ": Unknown directive"	"\n"
	"Pick directive from list:"						"\n";

void	put_unknown_directive_error(
				t_parser_state const *state,
				char const *token)
{
	register size_t	i;

	printf(
		g_directive_error_msg,
		state->filename,
		state->line_number,
		(int)(token - state->line_cpy), state->line,
		token,
		state->line + (int)(token - state->line_cpy) + ft_strlen(token),
		token - state->line_cpy + 1, token);
	i = 0;
	while (i < sizeof(g_directives) / sizeof(*g_directives))
	{
		printf(" %s", g_directives[i].identifier);
		++i;
	}
	printf("\n");
}
