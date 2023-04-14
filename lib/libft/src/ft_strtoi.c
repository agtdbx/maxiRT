/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtoi.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdubois <tdubois@student.42angouleme.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 14:43:12 by tdubois           #+#    #+#             */
/*   Updated: 2023/04/07 14:45:51 by tdubois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"

#include <errno.h>
#include <limits.h>
#include <stddef.h>
#include <stdbool.h>

int	ft_strtoi(
		char const *restrict nptr,
		char **restrict endptr)
{
	long	n;
	long	digit;
	bool	is_neg;

	nptr += ft_strspn(nptr, " \f\n\r\t\v");
	is_neg = (*nptr == '-');
	nptr += (ft_strspn(nptr, "+-") > 0);
	n = 0;
	while (ft_isdigit(*nptr))
	{
		digit = *nptr - '0';
		if (n < (INT_MIN + digit) / 10 || (INT_MAX - digit) / 10 < n)
		{
			errno = ERANGE;
			*endptr = (char *) nptr;
			if (is_neg)
				return ((int)INT_MIN);
			return ((int)INT_MAX);
		}
		n = n * 10 + (1 - 2 * is_neg) * digit;
		nptr++;
	}
	if (endptr != NULL)
		*endptr = (char *) nptr;
	return (n);
}
