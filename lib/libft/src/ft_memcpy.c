/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdubois <tdubois@student.42angouleme.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 18:09:46 by tdubois           #+#    #+#             */
/*   Updated: 2023/04/07 12:16:29 by tdubois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"

#include <stddef.h>

void	*ft_memcpy(
			void *restrict dst,
			void const *restrict src,
			size_t src_size)
{
	register char		*c_dst;
	register char const	*c_src;
	register size_t		i;

	c_dst = dst;
	c_src = src;
	i = 0;
	while (i < src_size)
	{
		c_dst[i] = c_src[i];
		i++;
	}
	return (dst);
}
