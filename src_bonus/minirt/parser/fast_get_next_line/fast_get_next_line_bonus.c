/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fast_get_next_line_bonus.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auguste <auguste@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 16:24:37 by auguste           #+#    #+#             */
/*   Updated: 2024/03/17 18:14:23 by auguste          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt/parser/fast_get_next_line/fast_get_next_line_bonus.h"

#include <stdlib.h>
#include <unistd.h>

static int	get_line_in_buffer(
				char buffer[FGNL_BUFFER_SIZE],
				char **line);
static int	get_line_in_file(
				int fd,
				char buffer[FGNL_BUFFER_SIZE],
				char **line);

char	*fast_get_next_line(
			int fd)
{
	static char	buffer[FGNL_BUFFER_SIZE] = {0};
	char	*line;
	int		i;

	line = NULL;
	if (get_line_in_buffer(buffer, &line))
		return (line);
	if (get_line_in_file(fd, buffer, &line))
		return (line);
	// add line before buffer, and free line if not null
	_fgnl_extend_str(&line, buffer);
	if (line == NULL)
		return (NULL);
	i = 0;
	while (line[i] != '\0')
	{
		buffer[i] = line[i];
		i++;
	}
	buffer[i] = '\0';
	free(line);
	return (NULL);
}

// Return 1 if there is a line in buffer
static int	get_line_in_buffer(
				char buffer[FGNL_BUFFER_SIZE],
				char **line)
{
	int	i;

	// Check if buffer is empty
	if (buffer[0] == '\0')
	{
		//printf("No\n");
		return (0);
	}

	// Finding newline or endline
	i = 0;
	while (buffer[i] != '\0' && buffer[i] != '\n')
		i++;

	// If newline found
	if (buffer[i] == '\n')
		return (_fgnl_copy_line_in_buffer(buffer, line, i));
	// Copy line part into line
	*line = ft_strdup(buffer);
	if (*line == NULL)
		return (0);
	// Clear buffer
	buffer[0] = '\0';
	return (0);
}

// Return 1 if there is a line in file
static int	get_line_in_file(
				int fd,
				char buffer[FGNL_BUFFER_SIZE],
				char **line)
{
	char	read_buffer[FGNL_BUFFER_SIZE];
	int		read_val;
	int		i;

	read_val = FGNL_BUFFER_SIZE - 1;
	while (read_val == FGNL_BUFFER_SIZE - 1)
	{
		// Read data from file
		read_val = read(fd, read_buffer, FGNL_BUFFER_SIZE - 1);
		if (read_val == -1)
			return (0);
		if (read_val == 0)
			return (1);
		read_buffer[read_val] = '\0';
		// Finding newline or endline
		i = 0;
		while (read_buffer[i] != '\0' && read_buffer[i] != '\n')
			i++;

		// Find newline
		if (read_buffer[i] == '\n')
			return (_fgnl_copy_read_line_in_line(buffer, read_buffer, line, i));
		_fgnl_extend_str(line, read_buffer);
	}
	return (1);
}
