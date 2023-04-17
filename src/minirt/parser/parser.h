/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdubois <tdubois@student.42angouleme.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 10:09:02 by tdubois           #+#    #+#             */
/*   Updated: 2023/04/17 16:23:02 by tdubois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include <minirt/scene/scene.h>
# include <minirt/parser/parser_field.h>
# include <minirt/parser/parser_errors.h>
# include <minirt/parser/parser_directives.h>

static const t_directive	g_directive_parsers[] = {
{"C", parse_camera,			"C <position> <orientation vector> <fov>"},
{"A", parse_ambient_light,	"A <brightness> <color>"},
{"L", parse_spotlight,		"L <position> <brightness> <color>"},
};

t_parsing_error	parse_scene_file(
					char const *path_to_file,
					t_scene *ret_scene);

t_parsing_error	parse_lines(
					int fd,
					char const *path_to_file,
					t_scene *ret_scene);

t_parsing_error	parse_directive(
					char const *filename,
					char const *line,
					int line_nbr,
					t_scene *ret_scene);

#endif//PARSER_H
