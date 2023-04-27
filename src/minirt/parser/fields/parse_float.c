/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_float.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdubois <tdubois@student.42angouleme.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 13:18:51 by tdubois           #+#    #+#             */
/*   Updated: 2023/04/27 16:23:51 by tdubois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt/parser/parser.h"
#include "minirt/utils/geometry.h"

#include <stdbool.h>

//############################################################################//
//#### DECLARATIONS ##########################################################//

t_error	parse_float(
			t_parser_state *state,
			void *data);

//############################################################################//
//#### DEFINITIONS ###########################################################//

t_error	parse_float(
			t_parser_state *state,
			void *data)
{
	float *const	x = data;
	char			*endptr;

	*x = ft_strtof(state->tok, &endptr);
	if (endptr[0] != '\0')
	{
		put_field_error(state, endptr, "Unexpected chars");
		return (FAILURE);
	}
	return (SUCCESS);
}
