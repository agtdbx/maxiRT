/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_directive.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdubois <tdubois@student.42angouleme.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 11:24:10 by tdubois           #+#    #+#             */
/*   Updated: 2023/04/17 15:56:45 by tdubois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt/parser/parser.h>
#include <minirt/scene/scene.h>
#include <libft/libft.h>

#include <stdio.h>
#include <stddef.h>

//############################################################################//
//#### DECLARATIONS ##########################################################//

t_parsing_error			parse_directive(
							char const *filename,
							char const *line,
							int line_nbr,
							t_scene *ret_scene);

static t_parsing_error	_use_associated_directive_parser(
							t_line_info	const *line_info,
							char *line,
							t_scene *ret_scene);

//############################################################################//
//#### DEFINITIONS ###########################################################//

t_parsing_error	parse_directive(
					char const *filename,
					char const *line,
					int line_nbr,
					t_scene *ret_scene)
{
	t_line_info const	line_info = {filename, line, line_nbr};
	char				*line_cpy;
	t_parsing_error		err;

	line_cpy = ft_strdup(line);
	if (line_cpy == NULL)
		return (PARSING_FAILURE);
	err = _use_associated_directive_parser(&line_info, line_cpy, ret_scene);
	ft_memdel(&line_cpy);
	return (err);
}

static t_parsing_error	_use_associated_directive_parser(
							t_line_info	const *line_info,
							char *line,
							t_scene *ret_scene)
{
	int		i;
	char	*identifier;
	char	*saveptr;

	i = 0;
	identifier = ft_strtok_r(line, " ", &saveptr);
	while (g_directive_parsers[i].identifier != NULL)
	{
		if (ft_strcmp(g_directive_parsers[i].identifier, identifier) == 0)
			return (g_directive_parsers[i].parser(line_info, saveptr, ret_scene));
		i++;
	}
	printf(g_unknown_directive_identifier_error_msg, 
		line_info->basename, line_info->line_nbr, line_info->line, identifier);
	return (PARSING_FAILURE);
}
