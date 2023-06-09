/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sftoa.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdubois <tdubois@student.42angouleme.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 13:38:45 by tdubois           #+#    #+#             */
/*   Updated: 2023/06/09 15:46:07 by tdubois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft/libft.h>

#include <math.h>
#include <float.h>
#include <stddef.h>

#define ERROR (-1)
#define STR_NAN "NaN"
#define STR_POS_INF "+inf"
#define STR_NEG_INF "-inf"

static size_t	_handle_finite_float(
					float x,
					char *buf,
					size_t buf_size);

static size_t	_handle_finite_float_with_exponent(
					float x,
					char *buf,
					size_t buf_size);

size_t	ft_sftoa(
			float x,
			char *buf,
			size_t buf_size)
{
	if (isnanf(x))
	{
		if (ft_strlcpy(buf, STR_NAN, buf_size) > buf_size - 1)
			return (ERROR);
		return (sizeof(STR_NAN) - 1);
	}
	if (isinff(x) == -1)
	{
		if (ft_strlcpy(buf, STR_NEG_INF, buf_size) > buf_size - 1)
			return (ERROR);
		return (sizeof(STR_NEG_INF) - 1);
	}
	if (isinff(x) == +1)
	{
		if (ft_strlcpy(buf, STR_POS_INF, buf_size) > buf_size - 1)
			return (ERROR);
		return (sizeof(STR_POS_INF) - 1);
	}
	if (x < 0.0f)
	{
		buf[0] = '-';
		return (_handle_finite_float_with_exponent(
				-x, buf + 1, ft_max(0, buf_size - 1)));
	}
	return (_handle_finite_float_with_exponent(x, buf, buf_size));
}

static size_t	_handle_finite_float_with_exponent(
					float x,
					char *buf,
					size_t buf_size)
{
	size_t	len;
	float	exp;

	exp = floorf(log10f(x));
	if (isinff(exp) || isnanf(exp))
	{
		return (_handle_finite_float(
				0.0f, buf, ft_min(buf_size, FLT_DIG + 2)));
	}
	if (fabs(exp) < FLT_DIG - 1)
	{
		return (_handle_finite_float(
				x, buf, ft_min(buf_size, FLT_DIG + 2)));
	}
	len = _handle_finite_float(
			x / powf(10, exp), buf, ft_min(buf_size, FLT_DIG + 2));
	if (len < buf_size - 1)
	{
		buf[len] = 'E';
		++len;
	}
	return (len + ft_sitoa((int)exp, buf + len, ft_max(0, buf_size - len)));
}

static size_t	_handle_finite_float(
					float x,
					char *buf,
					size_t buf_size)
{
	float	digit;
	float	before_dot;
	size_t	len;

	before_dot = truncf(x);
	len = ft_sitoa((int)before_dot, buf, buf_size);
	x -= before_dot;
	if (len < buf_size - 1)
	{
		buf[len] = '.';
		++len;
	}
	while (len < buf_size - 1)
	{
		x *= 10.0f;
		digit = roundf(x);
		buf[len] = (int)fmax(0.0f, digit) + '0';
		x -= digit;
		++len;
		if (isnanf(x) || isinf(x) || x == 0.0f)
			break ;
	}
	if (buf_size > 0)
		buf[len] = '\0';
	return (len);
}
