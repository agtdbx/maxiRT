/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_brightness.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdubois <tdubois@student.42angouleme.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 13:18:51 by tdubois           #+#    #+#             */
/*   Updated: 2023/06/09 15:32:57 by tdubois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt/parser/parser.h"

#include "libft/libft.h"

//############################################################################//
//#### DECLARATIONS ##########################################################//

t_error	parse_brightness(
			t_parser_state *state,
			void *data);

//############################################################################//
//#### DEFINITIONS ###########################################################//

t_error	parse_brightness(
			t_parser_state *state,
			void *data)
{
	float *const	brightness = data;

	if (parse_float(state, data) == FAILURE)
		return (FAILURE);
	if (*brightness < 0.0f || 1.0f < *brightness)
	{
		put_field_error(state, state->tok, "Invalid range");
		return (FAILURE);
	}
	return (SUCCESS);
}
