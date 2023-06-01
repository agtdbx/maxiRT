/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sitoa.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdubois <tdubois@student.42angouleme.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 10:56:32 by tdubois           #+#    #+#             */
/*   Updated: 2023/06/01 10:19:22 by tdubois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft/libft.h>

/**
 * @param[in] n
 * @param[out] buf
 * @param[in] buf_size
 */
size_t	ft_sitoa(
			int n,
			char *buf,
			size_t buf_size)
{
	register size_t	i;

	if (buf_size == 0)
		return (0);
	i = 0;
	if (n < 0 && i < buf_size - 1)
	{
		buf[0] = '-';
		++i;
	}
	if (n == 0 && i < buf_size - 1)
	{
		buf[i] = '0';
		++i;
	}
	while (n != 0 && i < buf_size - 1)
	{
		buf[i] = ft_abs(n % 10) + '0';
		n /= 10;
		++i;
	}
	buf[i] = '\0';
	ft_strrev(buf + (buf[0] == '-'));
	return (i);
}
