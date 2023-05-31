/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdubois <tdubois@student.42angouleme.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 18:07:11 by tdubois           #+#    #+#             */
/*   Updated: 2023/05/31 11:02:22 by tdubois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft/libft.h>

#include <stddef.h>

size_t	ft_strlcpy(
			char *restrict dst,
			char const *restrict src,
			size_t dst_size)
{
	register size_t	i;

	i = 0;
	while (i < dst_size && src[i] != '\0')
	{
		dst[i] = src[i];
		++i;
	}
	if (dst_size > 0)
		dst[i] = '\0';
	return (i);
}
