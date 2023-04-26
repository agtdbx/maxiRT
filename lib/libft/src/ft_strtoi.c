/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtoi.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdubois <tdubois@student.42angouleme.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 14:43:12 by tdubois           #+#    #+#             */
/*   Updated: 2023/04/26 09:13:32 by tdubois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"

#include <errno.h>
#include <limits.h>
#include <stddef.h>
#include <stdbool.h>

/**
 * Parses int from string representation
 *
 * @param[in] nptr String represention formated as /\s*(+|-)?\d+/
 * @param[out] endptr Pointer toward end of the representation.
 * @returns Parsed int
 */
int	ft_strtoi(
		char const *restrict nptr,
		char **restrict endptr)
{
	long	n;
	long	digit;
	bool	is_neg;

	nptr += ft_strspn(nptr, " \f\n\r\t\v");
	is_neg = (*nptr == '-');
	nptr += (ft_strchr("+-", nptr[0]) != 0);
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
	*endptr = (char *) nptr;
	return (n);
}
