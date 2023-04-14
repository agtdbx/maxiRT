/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsep.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdubois <tdubois@student.42angouleme.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 12:04:37 by tdubois           #+#    #+#             */
/*   Updated: 2023/04/07 12:13:25 by tdubois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"

#include <stddef.h>

char	*ft_strsep(
			char **restrict stringp,
			char const *restrict sep)
{
	size_t	len_til_sep;
	char	*tok;

	if (*stringp == NULL)
		return (NULL);
	tok = *stringp;
	len_til_sep = ft_strcspn(tok, sep);
	if (tok[len_til_sep] == '\0')
	{
		*stringp = NULL;
		return (tok);
	}
	tok[len_til_sep] = '\0';
	*stringp += len_til_sep + 1;
	return (tok);
}
