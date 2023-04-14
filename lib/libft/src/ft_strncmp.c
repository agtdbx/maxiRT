/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdubois <tdubois@student.42angouleme.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 02:58:00 by tdubois           #+#    #+#             */
/*   Updated: 2023/04/06 03:02:57 by tdubois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"

#include <stddef.h>

int	ft_strncmp(
		const char *s1,
		const char *s2,
		size_t n)
{
	register size_t					i;
	register unsigned char const	*str1;
	register unsigned char const	*str2;

	i = 0;
	str1 = (unsigned char *) s1;
	str2 = (unsigned char *) s2;
	if (n == 0)
		return (0);
	while (str1[i] == str2[i] && str1[i] != '\0' && i < n - 1)
		i++;
	return (str1[i] - str2[i]);
}
