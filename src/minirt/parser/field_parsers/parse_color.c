/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdubois <tdubois@student.42angouleme.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 10:59:20 by tdubois           #+#    #+#             */
/*   Updated: 2023/04/18 16:27:20 by tdubois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt/parser/parser.h>
#include <libft/libft.h>
#include <stdio.h>

//############################################################################//
//#### DECLARATIONS ##########################################################//

t_parsing_error			parse_color(
							t_line_info const *line_info,
							char const *field_name,
							char *field,
							void *ret_ptr);

static t_parsing_error	_parse_channels(
							t_line_info const *line_info,
							char const *field,
							char *field_cpy,
							t_color *ret_color);

static t_parsing_error	_parse_channel(
							t_line_info const *line_info,
							char const *field,
							char **field_cpy,
							int *ret_channel);

static t_parsing_error	_check_missing_or_empty_channel(
							t_line_info const *line_info,
							char const *field,
							char const *nptr);

static t_parsing_error	_check_leading_non_digit(
							t_line_info const *line_info,
							char const *field,
							char const *nptr);

//############################################################################//
//#### DEFINITIONS ###########################################################//

t_parsing_error	parse_color(
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

static t_parsing_error	_parse_channels(
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

static t_parsing_error	_parse_channel(
							t_line_info const *line_info,
							char const *field,
							char **field_cpy,
							int *ret_channel)
{
	char	*nptr;
	char	*endptr;

	nptr = ft_strsep(field_cpy, ",");
	if (_check_missing_or_empty_channel(
			line_info, field, nptr) == PARSING_FAILURE)
		return (PARSING_FAILURE);
	if (_check_leading_non_digit(line_info, field, nptr) == PARSING_FAILURE)
		return (PARSING_FAILURE);
	*ret_channel = ft_strtoi(nptr, &endptr);
	if (*ret_channel < 0 || 255 < *ret_channel)
	{
		printf(g_invalid_color_channel_range_error, line_info->basename,
			line_info->line_nbr, line_info->line, field, nptr);
		return (PARSING_FAILURE);
	}
	if (endptr[0] != '\0')
	{
		printf(g_color_channel_trailing_non_digit_error, line_info->basename,
			line_info->line_nbr, line_info->line, field, nptr);
		return (PARSING_FAILURE);
	}
	return (PARSING_SUCCESS);
}

static t_parsing_error	_check_missing_or_empty_channel(
							t_line_info const *line_info,
							char const *field,
							char const *nptr)
{
	if (nptr == NULL)
	{
		printf(g_missing_color_channel_error, line_info->basename,
			line_info->line_nbr, line_info->line, field);
		return (PARSING_FAILURE);
	}
	if (nptr[0] == '\0')
	{
		printf(g_empty_color_channel_error, line_info->basename,
			line_info->line_nbr, line_info->line, field);
		return (PARSING_FAILURE);
	}
	return (PARSING_SUCCESS);
}

static t_parsing_error	_check_leading_non_digit(
							t_line_info const *line_info,
							char const *field,
							char const *nptr)
{
	if (!ft_isdigit(nptr[0]))
	{
		printf(g_color_channel_leading_non_digit_error, line_info->basename,
			line_info->line_nbr, line_info->line, field, nptr);
		return (PARSING_FAILURE);
	}
	return (PARSING_SUCCESS);
}
