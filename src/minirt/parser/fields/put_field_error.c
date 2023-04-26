/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_field_error.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdubois <tdubois@student.42angouleme.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 16:27:24 by tdubois           #+#    #+#             */
/*   Updated: 2023/04/26 16:28:34 by tdubois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt/parser/parser.h"

#include <stdio.h>

void	put_field_error(
				t_parser_state *state,
				char const *token,
				char const *error)
{
	printf(
		"Error"						"\n"
		"<%s>: %zi: %ti: %s: %s"	"\n"
		"Usage: %s"					"\n",
			state->filename,
			state->line_number,
			token - state->line_cpy,
			token,
			error,
			state->field->usage);
}
