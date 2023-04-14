/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtof.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdubois <tdubois@student.42angouleme.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 11:20:01 by tdubois           #+#    #+#             */
/*   Updated: 2023/04/07 12:15:20 by tdubois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"

float	ft_strtof(
			char const *restrict nptr,
			char **restrict endptr)
{
	double	ret;
	double	exponent;

	ret = 0.0f;
	while (ft_isdigit(nptr[0]))
	{
		ret = ret * 10.0f + ((double)(nptr[0] - '0'));
		nptr++;
	}
	*endptr = (char *)nptr;
	if (nptr[0] != '.')
		return (ret);
	if (!ft_isdigit(nptr[1]))
		return (ret);
	nptr++;
	exponent = 0.1f;
	while (ft_isdigit(nptr[0]))
	{
		ret += ((double)(nptr[0] - '0')) * exponent;
		nptr++;
		exponent /= 10.0f;
	}
	*endptr = (char *)nptr;
	return (ret);
}
