/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_dot_obj_file_bonus.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auguste <auguste@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 13:18:51 by tdubois           #+#    #+#             */
/*   Updated: 2024/03/16 12:34:22 by auguste          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt/parser/parser_bonus.h"

#include "libft/libft.h"
#include "minirt/parser/dot_obj_file/dot_obj_file_bonus.h"
#include <fcntl.h>
#include <stdio.h>

//############################################################################//
//#### DECLARATIONS ##########################################################//

t_error	parse_dot_obj_file(
			t_parser_state *state,
			void *data);

//############################################################################//
//#### DEFINITIONS ###########################################################//
t_error	parse_dot_obj_file(
			t_parser_state *state,
			void *data)
{
	t_object_file *const	objf = data;
	int						fd;
	int						file_res;
	t_parse_dot_struct		parse_dot_struct;
	char					error[40];

	fd = open(state->tok, O_RDONLY);
	if (fd == -1)
	{
		put_field_error(state, state->tok, "Invalid file");
		return (FAILURE);
	}
	file_res = parse_dot_file(fd, &parse_dot_struct);
	if (file_res != PARSE_DOT_FILE_SUCCESS)
	{
		sprintf(error, "Parsing error on line %i", file_res);
		put_field_error(state, state->tok, error);
		return (FAILURE);
	}
	if (!apply_parsing_to_object_file(objf, &parse_dot_struct))
	{
		put_field_error(state, state->tok, "Apply parsing to object error");
		return (FAILURE);
	}
	return (SUCCESS);
}
