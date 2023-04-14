/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdubois <tdubois@student.42angouleme.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 02:51:01 by tdubois           #+#    #+#             */
/*   Updated: 2023/04/06 02:51:20 by tdubois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"

#include <stddef.h>

/** ft_strchr:
 *	  - returns a pointer toward the first occurence of byte c
 *	    in null terminated string str.
 *    - returns NULL if c is not found.
 */
char	*ft_strchr(
			char const *str,
			int c)
{
	char const	_c = c;

	while (*str != '\0' && *str != _c)
		str++;
	if (*str == _c)
		return ((char *)str);
	return (NULL);
}
