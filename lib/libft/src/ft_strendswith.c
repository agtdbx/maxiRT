/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strendswith.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdubois <tdubois@student.42angouleme.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 16:21:33 by tdubois           #+#    #+#             */
/*   Updated: 2023/04/06 16:22:33 by tdubois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"

#include <stdbool.h>
#include <stddef.h>

bool	ft_strendswith(
			char const *str,
			char const *suffix)
{
	size_t const	len_str = ft_strlen(str);
	size_t const	len_suffix = ft_strlen(suffix);

	if (len_str < len_suffix)
		return (false);
	return (ft_strcmp(str + len_str - len_suffix, suffix) == 0);
}
