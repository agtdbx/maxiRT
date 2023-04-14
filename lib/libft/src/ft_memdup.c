/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdubois <tdubois@student.42angouleme.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 09:12:14 by tdubois           #+#    #+#             */
/*   Updated: 2023/04/07 10:50:21 by tdubois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"

#include <stddef.h>
#include <stdlib.h>

void	*ft_memdup(
			void const *buf,
			size_t buf_size)
{
	char const *const	bytes = buf;
	char				*bytes_cpy;
	size_t				i;

	bytes_cpy = malloc(buf_size);
	if (bytes_cpy == NULL)
		return (NULL);
	i = 0;
	while (i < buf_size)
	{
		bytes_cpy[i] = bytes[i];
		i++;
	}
	return (bytes_cpy);
}
