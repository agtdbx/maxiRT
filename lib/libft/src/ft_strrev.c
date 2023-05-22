/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrev.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdubois <tdubois@student.42angouleme.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 12:28:55 by tdubois           #+#    #+#             */
/*   Updated: 2023/05/22 12:30:20 by tdubois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft/libft.h>

#include <stddef.h>//size_t

/**
 * reverses str in place.
 * @param[out] str
 */
void	ft_strrev(
			char *str)
{
	size_t const	len = ft_strlen(str);
	register size_t	i;
	char			tmp;

	i = 0;
	while (i * 2 < len)
	{
		tmp = str[i];
		str[i] = str[len - 1 - i];
		str[len - 1 - i] = tmp;
		i++;
	}
}
