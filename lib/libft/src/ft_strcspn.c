/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcspn.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdubois <tdubois@student.42angouleme.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 02:53:21 by tdubois           #+#    #+#             */
/*   Updated: 2023/04/06 02:55:17 by tdubois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"

#include <stddef.h>

size_t	ft_strcspn(
			char const *str,
			char const *reject)
{
	register size_t	len;

	len = 0;
	while (str[len] != '\0' && ft_strchr(reject, str[len]) == NULL)
		len++;
	return (len);
}
