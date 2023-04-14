/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdubois <tdubois@student.42angouleme.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 03:01:11 by tdubois           #+#    #+#             */
/*   Updated: 2023/04/06 03:02:06 by tdubois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"

int	ft_strcmp(
		const char *s1,
		const char *s2)
{
	register size_t					i;
	register unsigned char const	*str1;
	register unsigned char const	*str2;

	i = 0;
	str1 = (unsigned char *) s1;
	str2 = (unsigned char *) s2;
	while (str1[i] == str2[i] && str1[i] != '\0')
		i++;
	return (str1[i] - str2[i]);
}
