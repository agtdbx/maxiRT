/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_lines.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdubois <tdubois@student.42angouleme.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 10:34:21 by tdubois           #+#    #+#             */
/*   Updated: 2023/04/18 17:04:47 by tdubois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt/parser/parser.h>
#include <libft/libft.h>
#include <stdio.h>//TODO
#include <errno.h>
#include <string.h>

//############################################################################//
//#### DECLARATIONS ##########################################################//

t_parsing_error			parse_lines(
							int fd,
							char const *path_to_file,
							t_scene *ret_scene);

static t_parsing_error	loc_read_line(
							int fd,
							char const *basename,
							int line_nbr,
							char **ret_line);

static bool				loc_is_empty(
							char const *line);

//############################################################################//
//#### DEFINITIONS ###########################################################//

t_parsing_error	parse_lines(
					int fd,
					char const *path_to_file,
					t_scene *ret_scene)
{
	char const *const	basename = ft_basename(path_to_file);
	t_parsing_error		err;
	char				*line;
	int					line_nbr;

	line_nbr = 0;
	err = PARSING_SUCCESS;
	while (err != PARSING_FAILURE)
	{
		err = loc_read_line(fd, basename, line_nbr, &line);
		if (err == PARSING_FAILURE)
			return (PARSING_FAILURE);
		if (err == PARSING_FILE_END_ERR)
			return (PARSING_SUCCESS);
		if (loc_is_empty(line) == false)
			err = parse_directive(basename, line, line_nbr, ret_scene);
		ft_memdel(&line);
		line_nbr++;
	}
	return (err);
}

static t_parsing_error	loc_read_line(
							int fd,
							char const *basename,
							int line_nbr,
							char **ret_line)
{
	static t_gnl_buffer	save_buf = GNL_STATIC_INITIALIZER;

	errno = 0;
	*ret_line = ft_gnl_r(fd, save_buf);
	if (errno != 0)
	{
		printf(g_reading_error_msg, basename, line_nbr, strerror(errno));
		ft_memdel(ret_line);
		return (PARSING_FAILURE);
	}
	if (*ret_line == NULL)
	{
		return (PARSING_FILE_END_ERR);
	}
	(*ret_line)[ft_strcspn(*ret_line, "\n")] = '\0';
	return (PARSING_SUCCESS);
}

static bool	loc_is_empty(
				char const *line)
{
	return (line[ft_strspn(line, " ")] == '\0');
}
