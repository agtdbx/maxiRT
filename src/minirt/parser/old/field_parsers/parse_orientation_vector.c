/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_orientation_vector.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdubois <tdubois@student.42angouleme.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 14:41:09 by tdubois           #+#    #+#             */
/*   Updated: 2023/04/19 16:29:34 by tdubois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt/parser/parser.h>
#include <libft/libft.h>
#include <stdio.h>

//############################################################################//
//#### DECLARATIONS ##########################################################//

t_parsing_error			parse_orientation_vector(
							t_line_info const *line_info,
							char const *field_name,
							char *field,
							void *ret_ptr);

//############################################################################//
//#### DEFINITIONS ###########################################################//

t_parsing_error	parse_orientation_vector(
					t_line_info const *line_info,
					char const *field_name,
					char *field,
					void *ret_ptr)
{
	t_color *const	ret_color = ret_ptr;
	t_parsing_error	err;
	char			*field_cpy;

	(void) field_name;
	field_cpy = ft_strdup(field);
	if (field_cpy == NULL)
		return (PARSING_FAILURE);
	err = _parse_channels(line_info, field, field_cpy, ret_color);
	ft_memdel(&field_cpy);
	return (err);
}

static t_parsing_error	_parse_coord(
							t_line_info const *line_info,
							char const *field,
							char *field_cpy,
							t_color *ret_color)
{
	if (_parse_channel(
			line_info, field, &field_cpy, &ret_color->r) == PARSING_FAILURE)
		return (PARSING_FAILURE);
	if (_parse_channel(
			line_info, field, &field_cpy, &ret_color->g) == PARSING_FAILURE)
		return (PARSING_FAILURE);
	if (_parse_channel(
			line_info, field, &field_cpy, &ret_color->b) == PARSING_FAILURE)
		return (PARSING_FAILURE);
	if (field_cpy != NULL)
	{
		printf(g_too_many_color_channels_error, line_info->basename,
			line_info->line_nbr, line_info->line, field, field_cpy);
		return (PARSING_FAILURE);
	}
	return (PARSING_SUCCESS);
}
