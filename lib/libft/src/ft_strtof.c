/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtof.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouba <aderouba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 11:20:01 by tdubois           #+#    #+#             */
/*   Updated: 2023/07/24 15:25:25 by aderouba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"

#include <float.h>
#include <math.h>

/**
 * Parses float from string representation
 *
 * @param[in] nptr String represention formated as /\s*(+|-)?\d+(.\d+)?/
 * @param[out] endptr Pointer toward end of the representation.
 * @returns Parsed float
 */
float	ft_strtof(
			char const *restrict nptr,
			char **restrict endptr)
{
	double	ret;
	double	exponent;
	int		sign;

	*endptr = (char *)nptr;
	*endptr += ft_strspn(*endptr, " \f\n\r\t\v");
	sign = 1 - 2 * ((*endptr)[0] == '-');
	*endptr += (ft_strchr("+-", (*endptr)[0]) != 0 && ft_isdigit((*endptr)[1]));
	ret = 0.0;
	while (ft_isdigit((*endptr)[0]) && !isnan(ret) && isfinite(ret) && ret < FLT_MAX)
	{
		ret = ret * 10.0 + ((double)((*endptr)[0] - '0'));
		++(*endptr);
	}
	if ((*endptr)[0] != '.' || !ft_isdigit((*endptr)[1]))
		return (sign * ret);
	++(*endptr);
	exponent = 0.1;
	while (ft_isdigit((*endptr)[0]) && !isnan(ret) && isfinite(ret) && ret < FLT_MAX)
	{
		ret += ((double)((*endptr)[0] - '0')) * exponent;
		++(*endptr);
		exponent /= 10.0f;
	}
	return (sign * ret);
}
