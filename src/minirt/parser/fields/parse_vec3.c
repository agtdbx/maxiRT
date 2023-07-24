/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_vec3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouba <aderouba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 13:18:51 by tdubois           #+#    #+#             */
/*   Updated: 2023/07/24 15:43:45 by aderouba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt/parser/parser.h"

#include <stddef.h>
#include <stdbool.h>
#include <math.h>

#include "minirt/app/utils/geometry/geometry.h"

//############################################################################//
//#### DECLARATIONS ##########################################################//

t_error			parse_vec3(
					t_parser_state *state,
					void *data);

static t_error	_parse_one_coord(
					t_parser_state *state,
					float *ret);

static bool		_has_more_coords(
					t_parser_state *state);

//############################################################################//
//#### DEFINITIONS ###########################################################//

t_error	parse_vec3(
			t_parser_state *state,
			void *data)
{
	t_vec3 *const	vec = data;

	if (_parse_one_coord(state, &vec->x) == FAILURE
		|| _parse_one_coord(state, &vec->y) == FAILURE
		|| _parse_one_coord(state, &vec->z) == FAILURE
		|| _has_more_coords(state))
		return (FAILURE);
	return (SUCCESS);
}

static t_error	_parse_one_coord(
					t_parser_state *state,
					float *ret)
{
	char *const	coord = ft_strsep(&state->tok, ",");
	char		*endptr;

	if (coord == NULL)
		put_field_error(state,
			ft_strchr(state->tok_start, '\0'), "Missing coordinate");
	if (coord != NULL && coord[0] == '\0')
		put_field_error(state, coord, "Missing coordinate");
	if (coord == NULL || coord[0] == '\0')
		return (FAILURE);
	*ret = ft_strtof(coord, &endptr);
	if (endptr[0] != '\0')
	{
		put_field_error(state, endptr, "Unexpected chars");
		return (FAILURE);
	}
	if (isnan(*ret) || !isfinite(*ret) || g_scene_radius < fabsf(*ret))
	{
		put_field_error(state, coord, "Coordinate not in range [-1000,1000]");
		return (FAILURE);
	}
	if (state->tok != NULL)
		coord[ft_strlen(coord)] = ',';
	return (SUCCESS);
}

static bool	_has_more_coords(
				t_parser_state *state)
{
	if (state->tok != NULL)
	{
		--state->tok;
		state->tok[0] = ',';
		put_field_error(state, state->tok, "Unexpected chars");
		return (true);
	}
	return (false);
}
