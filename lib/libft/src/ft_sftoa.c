/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sftoa.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdubois <tdubois@student.42angouleme.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 13:38:45 by tdubois           #+#    #+#             */
/*   Updated: 2023/05/22 17:49:02 by tdubois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft/libft.h>

#include <stddef.h>

ssize_t	ft_sftoa(
			float x,
			char *buf,
			size_t buf_size)
{
	int const	before_dot = (int)x;
	ssize_t		before_dot_len;
	float const	decimal_part = x - (float)before_dot;
	int const	after_dot = (1.0f + decimal_part) * 10000.0f;
	ssize_t		after_dot_len;

	before_dot_len = ft_sitoa(before_dot, buf, buf_size);
	if (before_dot_len == -1)
		return (-1);
	if (decimal_part == 0.0f)
		return (before_dot_len);
	if ((size_t)before_dot_len >= buf_size - 1)
		return (-1);
	after_dot_len = ft_sitoa(
			after_dot, buf + before_dot_len, buf_size - before_dot_len);
	buf[before_dot_len] = '.';
	return (before_dot_len + after_dot_len + 2);
}
