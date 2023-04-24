/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_brightness.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdubois <tdubois@student.42angouleme.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 17:12:21 by tdubois           #+#    #+#             */
/*   Updated: 2023/04/17 17:42:34 by tdubois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt/parser/parser.h>
#include <libft/libft.h>
#include <stdio.h>
#include <stddef.h>

//############################################################################//
//#### DECLARATIONS ##########################################################//

t_parsing_error	parse_brightness(
					t_line_info const *line_info,
					char const *field_name,
					char *field,
					void *ret_ptr);

//############################################################################//
//#### DEFINITIONS ###########################################################//

t_parsing_error	parse_brightness(
					t_line_info const *line_info,
					char const *field_name,
					char *field,
					void *ret_ptr)
{
	float *const	brightness = ret_ptr;
	char			*endptr;

	endptr = NULL;
	if (!ft_isdigit(field[0]))
	{
		printf(g_invalid_brightness_format_err, line_info->basename,
			line_info->line_nbr, line_info->line, field);
		return (PARSING_FAILURE);
	}
	*brightness = ft_strtof(field, &endptr);
	if (*brightness < 0.0f || 1.0f < *brightness)
	{
		printf(g_invalid_brightness_range_err, line_info->basename,
			line_info->line_nbr, line_info->line, field);
		return (PARSING_FAILURE);
	}
	if (endptr[0] != '\0')
	{
		printf(g_unexpected_trailing_chars_err, line_info->basename,
			line_info->line_nbr, line_info->line, field_name, field, endptr);
		return (PARSING_FAILURE);
	}
	return (PARSING_SUCCESS);
}
