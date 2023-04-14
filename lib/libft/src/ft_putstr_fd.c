/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdubois <tdubois@student.42angouleme.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 02:42:16 by tdubois           #+#    #+#             */
/*   Updated: 2023/04/06 02:45:16 by tdubois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"

#include <unistd.h>
#include <sys/types.h>

ssize_t	ft_putstr_fd(
			char const *str,
			int fd)
{
	return (write(fd, str, ft_strlen(str)));
}
