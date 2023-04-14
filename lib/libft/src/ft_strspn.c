/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strspn.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdubois <tdubois@student.42angouleme.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 02:49:58 by tdubois           #+#    #+#             */
/*   Updated: 2023/04/06 02:55:27 by tdubois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"

#include <stddef.h>

size_t	ft_strspn(
			char const *str,
			char const *accept)
{
	register size_t	len;

	len = 0;
	while (str[len] != '\0' && ft_strchr(accept, str[len]) != NULL)
		len++;
	return (len);
}
