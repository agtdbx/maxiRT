/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_int.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdubois <tdubois@student.42angouleme.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 10:54:46 by tdubois           #+#    #+#             */
/*   Updated: 2023/06/09 15:31:55 by tdubois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_INT_H
# define PARSER_INT_H

# include <stddef.h>

# include "libft/libft.h"

# include "minirt/app/scene/scene.h"

typedef struct s_directive	t_directive;
typedef struct s_field		t_field;

//**** PARSER STATE **********************************************************//

typedef struct s_parser_state
{
	char const			*filename;
	char const			*line;
	size_t				line_number;

	char const			*line_cpy;
	t_directive const	*directive;

	t_field const		*field;
	char				*tok;
	char				*tok_start;

	t_scene				*scene;
}	t_parser_state;

t_error	parse_file(
			char const *path_to_file,
			t_scene *scene);

t_error	parse_directive(
			t_parser_state *state);

//**** PARSER FIELDS *********************************************************//

typedef t_error				(*t_field_cb)(t_parser_state *state, void *data);

struct s_field
{
	char const		*identifier;
	char const		*usage;

	t_field_cb		callback;
};

t_error	parse_field(
			t_parser_state *state,
			t_field const *field,
			void *data);

t_error	parse_vec3(
			t_parser_state *state,
			void *data);

t_error	parse_direction(
			t_parser_state *state,
			void *data);

t_error	parse_color(
			t_parser_state *state,
			void *data);

t_error	parse_float(
			t_parser_state *state,
			void *data);

t_error	parse_brightness(
			t_parser_state *state,
			void *data);

t_error	parse_fov(
			t_parser_state *state,
			void *data);

t_error	parse_diameter(
			t_parser_state *state,
			void *data);

//**** PARSER DIRECTIVES *****************************************************//

typedef t_error				(*t_directive_cb)(t_parser_state *state);

struct s_directive
{
	char const		*identifier;
	char const		*usage;

	t_directive_cb	callback;
};

t_error	parse_lines(
			int fd,
			char const *filename,
			t_scene *scene);

t_error	parse_camera(
			t_parser_state *state);

t_error	parse_ambient_light(
			t_parser_state *state);

t_error	parse_spotlight(
			t_parser_state *state);

t_error	parse_sphere(
			t_parser_state *state);

//**** PARSER ERROR LOGGING **************************************************//

void	put_directive_error(
			t_parser_state *state,
			char const *token,
			char const *error);

void	put_unknown_directive_error(
			t_parser_state const *state,
			char const *token);

void	put_field_error(
			t_parser_state *state,
			char const *token,
			char const *error);

#endif//PARSER_INT_H
