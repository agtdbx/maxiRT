/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sftoa.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdubois <tdubois@student.42angouleme.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 13:38:45 by tdubois           #+#    #+#             */
/*   Updated: 2023/05/23 10:43:50 by tdubois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft/libft.h>

#include <math.h>
#include <stddef.h>

#define ERROR (-1)
#define STR_NAN "NaN"
#define STR_POS_INF "+inf"
#define STR_NEG_INF "-inf"

ssize_t	_handle_finite_float(
			float x,
			char *buf,
			size_t buf_size);

ssize_t	ft_sftoa(
			float x,
			char *buf,
			size_t buf_size)
{
	if (isnanf(x))
	{
		if (ft_strlcpy(buf, STR_NAN, buf_size) > buf_size - 1)
			return (ERROR);
		return (sizeof(STR_NAN));
	}
	if (isinff(x) == -1)
	{
		if (ft_strlcpy(buf, STR_NEG_INF, buf_size) > buf_size - 1)
			return (ERROR);
		return (sizeof(STR_NEG_INF));
	}
	if (isinff(x) == +1)
	{
		if (ft_strlcpy(buf, STR_POS_INF, buf_size) > buf_size - 1)
			return (ERROR);
		return (sizeof(STR_POS_INF));
	}
	return (_handle_finite_float(x, buf, buf_size));
}

ssize_t	_handle_finite_float(
			float x,
			char *buf,
			size_t buf_size)
{
	int		exp;
	float	before_dot;
	float	after_dot;

	if (x)
	after_dot = modff(x, &before_dot);

}


{
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
