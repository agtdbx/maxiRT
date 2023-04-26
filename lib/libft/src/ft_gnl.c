/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_gnl.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdubois <tdubois@student.42angouleme.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 13:13:12 by tdubois           #+#    #+#             */
/*   Updated: 2023/04/26 13:18:33 by tdubois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"

/**
 * Read one line from fd. Line should be freed by the calling context.
 * Internally uses a static buffer, use ft_gnl_r if reentrancy matters.
 *
 * @param[in] fd The file descriptor to read from
 * @returns The line as a heap allocated buffer.
 */
char	*ft_gnl(
			int fd)
{
	static t_gnl_buffer	buffer = GNL_STATIC_INITIALIZER;

	return (ft_gnl_r(fd, buffer));
}
