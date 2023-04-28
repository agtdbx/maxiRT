/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_field.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdubois <tdubois@student.42angouleme.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 12:37:40 by tdubois           #+#    #+#             */
/*   Updated: 2023/04/28 16:25:21 by tdubois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt/parser/parser.h"

#include "libft/libft.h"
#include "minirt/parser/parser_int.h"

t_error	parse_field(
			t_parser_state *state,
			t_field const *field,
			void *data)
{
	char *const	tok = ft_strtok(NULL, " ");

	if (tok == NULL)
	{
		put_field_error(state, tok, "Missing field");
		return (FAILURE);
	}
	state->field = field;
	state->tok = tok;
	state->tok_start = tok;
	return (field->callback(state, data));
}
