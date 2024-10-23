/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_lines.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auguste <auguste@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 11:43:54 by tdubois           #+#    #+#             */
/*   Updated: 2024/03/17 18:16:50 by auguste          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt/parser/parser.h"

#include <errno.h>
#include <stdio.h>

#include "libft/libft.h"

#include "minirt/app/scene/scene.h"

#include "minirt/parser/fast_get_next_line/fast_get_next_line.h"

static t_error	_get_line(
					int fd,
					t_parser_state *state);
static bool		_is_blank(
					char const *line);

/**
 * Parses each lines, one at a time.
 *
 * @param[in] fd File descriptor of config file
 * @param[in] filename For error reports
 * @param[out] scene Scene to fill up with parsed data
 * @returns SUCCESS or FAILURE whether parsing has has been succesful or not
 */
t_error	parse_lines(
			int fd,
			char const *filename,
			t_scene *scene)
{
	t_parser_state	state;
	t_error			err;

	state.line_number = 1;
	state.scene = scene;
	state.filename = filename;
	err = SUCCESS;
	while (err == SUCCESS)
	{
		err = _get_line(fd, &state);
		if (err == FAILURE || state.line == NULL)
			break ;
		if (!_is_blank(state.line))
			err = parse_directive(&state);
		ft_memdel(&state.line);
		++state.line_number;
	}
	return (err);
}

/**
 * Wrapper around gnl that removes trailing newline, and report errors.
 *
 * @param[in] fd File descriptor of config file
 * @param[out] state Parser state handle
 * @returns SUCCESS or FAILURE whether parsing has has been succesful or not
 */
static t_error	_get_line(
					int fd,
					t_parser_state *state)
{
	char	*line;

	errno = 0;
	//line = ft_gnl(fd);
	line = fast_get_next_line(fd);
	if (errno != 0)
	{
		perror("Error\nfatal");
		return (FAILURE);
	}
	if (line != NULL)
		line[ft_strcspn(line, "\n")] = '\0';
	state->line = line;
	return (SUCCESS);
}

/**
 * Check if line is blank. Directive parser is not called in that case.
 *
 * @param[in] line The line to check
 * @returns Answer
 */
static bool	_is_blank(
				char const *line)
{
	return (line[ft_strspn(line, " \n")] == '\0');
}
