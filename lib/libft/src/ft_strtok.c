/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtok.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdubois <tdubois@student.42angouleme.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 13:43:39 by tdubois           #+#    #+#             */
/*   Updated: 2023/04/26 13:47:53 by tdubois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"

/**
 * See man strtok (3). And strtok_r for the reentrant version.
 *
 * @param[in] str
 * @param[in] sep
 * @returns A token
 */
char	*ft_strtok(
			char *restrict str,
			char const *restrict sep)
{
	static char	*saveptr;

	return (ft_strtok_r(str, sep, &saveptr));
}
