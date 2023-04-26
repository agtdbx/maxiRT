/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_int.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdubois <tdubois@student.42angouleme.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 10:54:46 by tdubois           #+#    #+#             */
/*   Updated: 2023/04/26 17:55:04 by tdubois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_INT_H
# define PARSER_INT_H

# include "minirt/scene/scene.h"

# include "libft/libft.h"

# include <stddef.h>

typedef struct s_directive	t_directive;

//**** PARSER STATE **********************************************************//

typedef struct s_parser_state
{
	char const			*filename;
	char const			*line;
	size_t				line_number;

	char const			*line_cpy;
	t_directive const	*directive;

	t_scene		*scene;
}	t_parser_state;

//**** PARSER FIELDS *********************************************************//

typedef t_error	(*t_field_cb)(t_parser_state *state);

typedef struct s_field
{
	char const		*identifier;
	char const		*usage;

	t_field_cb		callback;
}	t_field;

t_error	parse_field(
			t_parser_state *state,
			t_field const *field,
			void *data);

//**** PARSER DIRECTIVES *****************************************************//

typedef t_error	(*t_directive_cb)(t_parser_state *state);

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

//**** PARSER ERROR LOGGING **************************************************//

void	put_directive_error(
				t_parser_state *state,
				char const *token,
				char const *error);

void	put_field_error(
				t_parser_state *state,
				char const *token,
				char const *error);

#endif//PARSER_INT_H
