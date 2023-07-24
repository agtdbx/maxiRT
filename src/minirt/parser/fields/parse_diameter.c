/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_diameter.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouba <aderouba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 13:18:51 by tdubois           #+#    #+#             */
/*   Updated: 2023/07/05 16:13:27 by aderouba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt/parser/parser.h"

#include "libft/libft.h"

//############################################################################//
//#### DECLARATIONS ##########################################################//

t_error	parse_diameter(
			t_parser_state *state,
			void *data);

//############################################################################//
//#### DEFINITIONS ###########################################################//

t_error	parse_diameter(
			t_parser_state *state,
			void *data)
{
	float *const	diameter = data;

	if (parse_float(state, data) == FAILURE)
		return (FAILURE);
	if (*diameter < 0.0f)
	{
		put_field_error(state, state->tok, "Invalid range");
		return (FAILURE);
	}
	return (SUCCESS);
}
