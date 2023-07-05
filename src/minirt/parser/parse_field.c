/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_field.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouba <aderouba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 12:37:40 by tdubois           #+#    #+#             */
/*   Updated: 2023/07/05 18:18:36 by aderouba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt/parser/parser.h"

#include "libft/libft.h"
#include "minirt/parser/parser_int.h"

#include <stdio.h>

#define RED "\e[91m"
#define NC "\e[0m"

static const char	g_field_error_msg[] = \
	"Error"								"\n"
	"%s:"								"\n"
	"row %03zi> %.*s" RED"%s"NC "%s"	"\n"
	"col %03ti> " RED"%s"NC ": %s"		"\n"
	"Usage: %s"							"\n";

t_error	parse_field(
			t_parser_state *state,
			t_field const *field,
			void *data)
{
	char *const	tok = ft_strtok(NULL, " ");
	char		*token;

	if (tok == NULL)
	{
		token = state->tok_start + ft_strlen(state->tok_start);
		printf(
			g_field_error_msg,
			state->filename,
			state->line_number,
			(int)(token - state->line_cpy), state->line,
			" <field>",
			state->line + (int)(token - state->line_cpy) + ft_strlen(token),
			token - state->line_cpy + 1, token, "Missing field",
			state->directive->usage);
		return (FAILURE);
	}
	state->field = field;
	state->tok = tok;
	state->tok_start = tok;
	return (field->callback(state, data));
}
