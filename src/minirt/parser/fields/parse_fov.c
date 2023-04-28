/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_fov.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdubois <tdubois@student.42angouleme.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 13:18:51 by tdubois           #+#    #+#             */
/*   Updated: 2023/04/28 13:15:57 by tdubois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt/parser/parser.h>
#include <libft/libft.h>

//############################################################################//
//#### DECLARATIONS ##########################################################//

t_error	parse_fov(
			t_parser_state *state,
			void *data);

//############################################################################//
//#### DEFINITIONS ###########################################################//

t_error	parse_fov(
			t_parser_state *state,
			void *data)
{
	float *const	fov = data;

	if (parse_float(state, data) == FAILURE)
		return (FAILURE);
	if (*fov < 0.0f || 180.0f < *fov)
	{
		put_field_error(state, state->tok, "Invalid range");
		return (FAILURE);
	}
	return (SUCCESS);
}
