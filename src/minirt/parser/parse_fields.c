/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_fields.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdubois <tdubois@student.42angouleme.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 15:35:12 by tdubois           #+#    #+#             */
/*   Updated: 2023/04/18 17:28:17 by tdubois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt/parser/parser.h>
#include <libft/libft.h>
#include <stdio.h>

//############################################################################//
//#### DECLARATIONS ##########################################################//

t_parsing_error	parse_fields(
					t_line_info const *line_info,
					char *line,
					t_field const *fields);

//############################################################################//
//#### DEFINITIONS ###########################################################//

t_parsing_error	parse_fields(
					t_line_info const *line_info,
					char *line,
					t_field const *fields)
{
	char	*saveptr;
	char	*field;

	field = ft_strtok_r(line, " ", &saveptr);
	while (field != NULL && fields->name != NULL)
	{
		if (fields->parser(
				line_info, fields->name, field, fields->ptr) == PARSING_FAILURE)
			return (PARSING_FAILURE);
		fields++;
		field = ft_strtok_r(NULL, " ", &saveptr);
	}
	if (fields->name != NULL)
	{
		printf(g_missing_field_error, line_info->basename, line_info->line_nbr,
			line_info->line, fields->name);
		return (PARSING_FAILURE);
	}
	if (field != NULL)
	{
		printf(g_too_many_fields_error, line_info->basename,
			line_info->line_nbr, line_info->line, field, saveptr);
		return (PARSING_FAILURE);
	}
	return (PARSING_SUCCESS);
}
