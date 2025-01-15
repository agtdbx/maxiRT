/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdubois <tdubois@student.42angouleme.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 13:18:51 by tdubois           #+#    #+#             */
/*   Updated: 2023/06/03 00:36:47 by tdubois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt/parser/parser.h"

#include <stdbool.h>

//############################################################################//
//#### DECLARATIONS ##########################################################//

t_error			parse_color(
					t_parser_state *state,
					void *data);

static t_error	_parse_one_channel(
					t_parser_state *state,
					float *ret);

static bool		_has_more_channels(
					t_parser_state *state);

//############################################################################//
//#### DEFINITIONS ###########################################################//

t_error	parse_color(
			t_parser_state *state,
			void *data)
{
	t_color *const	color = data;

	if (_parse_one_channel(state, &color->r) == FAILURE
		|| _parse_one_channel(state, &color->g) == FAILURE
		|| _parse_one_channel(state, &color->b) == FAILURE
		|| _has_more_channels(state))
		return (FAILURE);
	color->a = 255;
	return (SUCCESS);
}

static t_error	_parse_one_channel(
					t_parser_state *state,
					float *ret)
{
	char *const	channel = ft_strsep(&state->tok, ",");
	char		*endptr;

	if (channel == NULL)
		put_field_error(state,
			ft_strchr(state->tok_start, '\0'), "Missing color channel");
	if (channel != NULL && channel[0] == '\0')
		put_field_error(state, channel, "Missing color channel");
	if (channel == NULL || channel[0] == '\0')
		return (FAILURE);
	*ret = ft_strtoi(channel, &endptr);
	if (endptr[0] != '\0')
	{
		put_field_error(state, endptr, "Unexpected chars");
		return (FAILURE);
	}
	if (*ret < 0 || 255 < *ret)
	{
		put_field_error(state, channel, "Invalid range");
		return (FAILURE);
	}
	if (state->tok != NULL)
		channel[ft_strlen(channel)] = ',';
	return (SUCCESS);
}

static bool	_has_more_channels(
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
