/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdubois <tdubois@student.42angouleme.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 02:46:23 by tdubois           #+#    #+#             */
/*   Updated: 2023/04/06 02:47:19 by tdubois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"

#include <sys/types.h>
#include <unistd.h>

ssize_t	ft_putstr(
			char const *str)
{
	return (ft_putstr_fd(str, STDOUT_FILENO));
}
