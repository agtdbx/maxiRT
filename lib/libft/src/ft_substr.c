/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdubois <tdubois@student.42angouleme.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 18:11:43 by tdubois           #+#    #+#             */
/*   Updated: 2023/04/06 18:11:48 by tdubois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"

#include <stdlib.h>
#include <stddef.h>

char	*ft_substr(
			char const *src,
			size_t start,
			size_t len)
{
	char	*substr;

	if (ft_strlen(src) < start)
		return (ft_strdup(""));
	substr = malloc(len + 1);
	if (substr == NULL)
		return (NULL);
	ft_strlcpy(substr, src + start, len);
	return (substr);
}
