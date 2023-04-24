/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_directives.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdubois <tdubois@student.42angouleme.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 11:40:07 by tdubois           #+#    #+#             */
/*   Updated: 2023/04/18 14:45:12 by tdubois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_DIRECTIVES_H
# define PARSER_DIRECTIVES_H

# include <minirt/parser/parser_errors.h>
# include <minirt/scene/scene.h>

typedef struct s_line_info
{
	char const	*basename;
	char const	*line;
	int			line_nbr;
}	t_line_info;

typedef t_parsing_error	t_directive_cb(
							t_line_info const *line_info,
							char *line,
							t_scene *ret_scene);

typedef struct s_directive
{
	char const		*identifier;
	t_directive_cb	*parser;
	char const		*usage;
}	t_directive;

t_parsing_error	parse_camera(
					char const *basename,
					char const *line,
					int line_nbr,
					t_scene *ret_scene);

t_parsing_error	parse_ambient_light(
					t_line_info const *line_info,
					char *line,
					t_scene *ret_scene);

t_parsing_error	parse_spotlight(
					t_line_info const *line_info,
					char *line,
					t_scene *ret_scene);

#endif//PARSER_DIRECTIVES_H
