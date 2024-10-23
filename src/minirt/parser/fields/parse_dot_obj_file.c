/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_dot_obj_file.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auguste <auguste@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 13:18:51 by tdubois           #+#    #+#             */
/*   Updated: 2024/03/16 16:42:12 by auguste          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt/parser/parser.h"

#include "libft/libft.h"
#include "minirt/parser/dot_obj_file/dot_obj_file.h"
#include <fcntl.h>
#include <unistd.h>

//############################################################################//
//#### DECLARATIONS ##########################################################//

t_error	parse_dot_obj_file(
			t_parser_state *state,
			void *data);
static void	create_line_error_message(char *msg, int line);

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
		close(fd);
		put_field_error(state, state->tok, "Invalid file");
		return (FAILURE);
	}
	parse_dot_struct_add_init(&parse_dot_struct);
	file_res = parse_dot_file(fd, &parse_dot_struct);
	close(fd);
	if (file_res != PARSE_DOT_FILE_SUCCESS)
	{
		create_line_error_message(error, file_res);
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


static void	create_line_error_message(char *msg, int line)
{
	char	buf[11];
	int		i;

	ft_strlcpy(msg, "Parsing error on line ", 23);
	ft_sitoa(line, buf, 11);
	i = 0;
	while (buf[i] != '\0')
	{
		msg[22 + i] = buf[i];
		i++;
	}
	msg[22 + i] = '\0';
}
