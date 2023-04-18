/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_gnl_r.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdubois <tdubois@student.42angouleme.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 18:06:50 by tdubois           #+#    #+#             */
/*   Updated: 2023/04/18 13:19:17 by tdubois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"

#include <unistd.h>
#include <stdlib.h>
#include <stddef.h>

char		*ft_gnl_r(
				int fd,
				t_gnl_buffer save_buf);

static char	*ft_gnl_r_rec(
				int fd,
				t_gnl_buffer save_buf,
				size_t len);

////////////////////////////////////////////////////////////////////////////////

char	*ft_gnl_r(
			int fd,
			t_gnl_buffer save_buf)
{
	t_gnl_buffer	head_buf;
	char			*line;
	int				line_len;

	ft_strlcpy(head_buf, save_buf, sizeof(t_gnl_buffer));
	line_len = ft_strcspn(head_buf, "\n");
	if (head_buf[line_len] == '\n')
	{
		line = ft_substr(head_buf, 0, line_len + 1);
		if (line == NULL)
			return (NULL);
		ft_strlcpy(save_buf, head_buf + line_len + 1, sizeof(t_gnl_buffer));
		return (line);
	}
	line = ft_gnl_r_rec(fd, save_buf, line_len);
	if (line == NULL)
		return (NULL);
	ft_memcpy(line, head_buf, line_len);
	return (line);
}

static char	*ft_gnl_r_rec(
				int fd,
				t_gnl_buffer save_buf,
				size_t line_len)
{
	t_gnl_buffer	read_buf;
	char			*line;
	int				read_ret;

	read_ret = read(fd, read_buf, sizeof(t_gnl_buffer) - 1);
	if (read_ret == -1)
		return (NULL);
	read_buf[read_ret] = '\0';
	if (read_ret == 0 && line_len == 0)
		return (NULL);
	read_ret = ft_strcspn(read_buf, "\n");
	read_ret += (read_buf[read_ret] == '\n');
	if (read_ret != sizeof(t_gnl_buffer) || read_buf[read_ret - 1] == '\n')
	{
		line = malloc(line_len + read_ret + 1);
		if (line != NULL)
			line[line_len + read_ret] = '\0';
		ft_strlcpy(save_buf, read_buf + read_ret, sizeof(t_gnl_buffer));
	}
	else
		line = ft_gnl_r_rec(fd, save_buf, line_len + sizeof(t_gnl_buffer));
	if (line == NULL)
		return (NULL);
	ft_memcpy(line + line_len, read_buf, read_ret);
	return (line);
}
