/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fast_get_next_line_utils_bonus.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auguste <auguste@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 16:24:37 by auguste           #+#    #+#             */
/*   Updated: 2024/03/17 18:13:42 by auguste          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt/parser/fast_get_next_line/fast_get_next_line_bonus.h"

#include <stdlib.h>

int	_fgnl_copy_line_in_buffer(
				char buffer[FGNL_BUFFER_SIZE],
				char **line,
				int i)
{
	int		j;
	char	tmp;

	// Copy it into line
	tmp = buffer[i + 1];
	buffer[i + 1] = '\0';
	*line = ft_strdup(buffer);
	buffer[i + 1] = tmp;
	if (*line == NULL)
		return (0);
	// Buffer shift
	i++;
	j = 0;
	while (buffer[i + j] != '\0')
	{
		buffer[j] = buffer[i + j];
		j++;
	}
	buffer[j] = '\0';
	return (1);
}

int	_fgnl_copy_read_line_in_line(
				char buffer[FGNL_BUFFER_SIZE],
				char read_buffer[FGNL_BUFFER_SIZE],
				char **line,
				int i)
{
	int		j;
	char	tmp;

	tmp = read_buffer[i + 1];
	read_buffer[i + 1] = '\0';
	_fgnl_extend_str(line, read_buffer);
	read_buffer[i + 1] = tmp;
	i++;
	j = 0;
	while (read_buffer[i + j] != '\0')
	{
		buffer[j] = read_buffer[i + j];
		j++;
	}
	buffer[j] = '\0';
	return (1);
}


void	_fgnl_extend_str(
				char **str,
				char *to_add)
{
	int		len;
	int		i;
	char	*new;

	if (to_add == NULL)
		return ;
	new = malloc(sizeof(char) * (ft_strlen(*str) + ft_strlen(to_add) + 1));
	if (new == NULL)
		return ;
	len = 0;
	while ((*str) && (*str)[len] != '\0')
	{
		new[len] = (*str)[len];
		len++;
	}
	i = 0;
	while (to_add && to_add[i] != '\0')
	{
		new[len + i] = to_add[i];
		i++;
	}
	new[len + i] = '\0';
	if (*str != NULL)
		free(*str);
	*str = new;
}
