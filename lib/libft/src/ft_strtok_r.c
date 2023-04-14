/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtok_r.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdubois <tdubois@student.42angouleme.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 01:29:00 by tdubois           #+#    #+#             */
/*   Updated: 2023/04/07 12:14:19 by tdubois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"

#include <stddef.h>

char	*ft_strtok_r(
			char *restrict str,
			char const *restrict sep,
			char **restrict saveptr)
{
	char	*tok;

	if (str != NULL)
		*saveptr = NULL;
	else if (*saveptr == NULL)
		return (NULL);
	if (str == NULL)
		tok = *saveptr;
	else
		tok = str;
	tok += ft_strspn(tok, sep);
	if (tok[0] == '\0')
	{
		*saveptr = NULL;
		return (NULL);
	}
	*saveptr = tok + ft_strcspn(tok, sep);
	*saveptr += ft_strspn(*saveptr, sep);
	tok[ft_strcspn(tok, sep)] = '\0';
	return (tok);
}
