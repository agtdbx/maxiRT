/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_direction.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdubois <tdubois@student.42angouleme.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 13:18:51 by tdubois           #+#    #+#             */
/*   Updated: 2023/06/09 15:33:27 by tdubois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt/parser/parser.h"

#include <stdbool.h>
#include <math.h>

#include "minirt/app/utils/geometry/geometry.h"

//############################################################################//
//#### DECLARATIONS ##########################################################//

t_error	parse_direction(
			t_parser_state *state,
			void *data);

//############################################################################//
//#### DEFINITIONS ###########################################################//

t_error	parse_direction(
			t_parser_state *state,
			void *data)
{
	t_vec3 *const	vec = data;

	if (parse_vec3(state, data) == FAILURE)
		return (FAILURE);
	if (fabs(vec3_norm(vec) - 1.0f) > 0.05)
	{
		put_field_error(state, state->tok_start, "Invalid norm");
		return (FAILURE);
	}
	return (SUCCESS);
}
