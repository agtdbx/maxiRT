/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdubois <tdubois@student.42angouleme.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 17:30:34 by tdubois           #+#    #+#             */
/*   Updated: 2023/04/26 17:33:39 by tdubois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"

void	*ft_memset(
			void *s,
			int c,
			size_t n)
{
	unsigned char *const	buffer = s;
	register size_t			i;

	i = 0;
	while (i < n)
	{
		buffer[i] = c;
		i++;
	}
	return (s);
}
