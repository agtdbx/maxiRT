/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_field.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdubois <tdubois@student.42angouleme.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 16:17:54 by tdubois           #+#    #+#             */
/*   Updated: 2023/04/18 16:51:50 by tdubois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_FIELD_H
# define PARSER_FIELD_H

# include <minirt/parser/parser_directives.h>
# include <minirt/parser/parser_errors.h>

typedef t_parsing_error	t_field_cb(
							t_line_info const *line_info,
							char const *field_name,
							char *field,
							void *ret_ptr);

typedef struct s_field
{
	char const	*name;
	void		*ptr;
	t_field_cb	*parser;
}	t_field;

t_parsing_error	parse_fields(
					t_line_info const *line_info,
					char *line,
					t_field const *fields);

t_parsing_error	parse_brightness(
					t_line_info const *line_info,
					char const *field_name,
					char *field,
					void *ret_ptr);

t_parsing_error	parse_color(
					t_line_info const *line_info,
					char const *field_name,
					char *field,
					void *ret_ptr);

t_parsing_error	parse_position(
					t_line_info const *line_info,
					char const *field_name,
					char *field,
					void *ret_ptr);

#endif//PARSER_FIELD_H
