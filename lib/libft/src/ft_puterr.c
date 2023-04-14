/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puterr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdubois <tdubois@student.42angouleme.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 02:47:34 by tdubois           #+#    #+#             */
/*   Updated: 2023/04/06 02:47:54 by tdubois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"

#include <sys/types.h>
#include <unistd.h>

ssize_t	ft_puterr(
			char const *str)
{
	return (ft_putstr_fd(str, STDERR_FILENO));
}
