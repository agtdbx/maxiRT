/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdubois <tdubois@student.42angouleme.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 17:34:43 by tdubois           #+#    #+#             */
/*   Updated: 2023/04/26 17:36:26 by tdubois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"

#include <stddef.h>

void	*ft_bzero(
			void *s,
			size_t n)
{
	return (ft_memset(s, 0, n));
}
