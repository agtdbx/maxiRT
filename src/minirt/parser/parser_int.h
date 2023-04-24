/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_int.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdubois <tdubois@student.42angouleme.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 10:54:46 by tdubois           #+#    #+#             */
/*   Updated: 2023/04/24 17:05:32 by tdubois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_INT_H
# define PARSER_INT_H

# include <minirt/scene/scene.h>

# include <stddef.h>

//**** PARSER STATE **********************************************************//

typedef struct s_parser_state
{
	char const	*filename;
	char const	*line;
	size_t		row;
	size_t		col;

	t_scene		*scene;
}	t_parser_state;

//**** PARSER ERRORS *********************************************************//

typedef enum e_parser_error
{
	PARSING_SUCCESS,
	PARSING_FAILURE,
}	t_parser_error;

//**** PARSER DIRECTIVES *****************************************************//

typedef t_parser_error	(*t_directive_cb)(t_parser_state *state);

typedef struct s_directive
{
	char const		*identifier;
	char const		*usage;

	t_directive_cb	callback;
}	t_directive;

#endif//PARSER_INT_H
