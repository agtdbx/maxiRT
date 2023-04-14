/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_basename.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdubois <tdubois@student.42angouleme.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 16:27:30 by tdubois           #+#    #+#             */
/*   Updated: 2023/04/06 16:32:23 by tdubois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"

char	*ft_basename(
			char const *path_to_file)
{
	size_t	len_until_path_sep;

	while (*path_to_file != '\0')
	{
		len_until_path_sep = ft_strcspn(path_to_file, "/");
		if (path_to_file[len_until_path_sep] == '\0')
			break ;
		path_to_file += len_until_path_sep + 1;
	}
	return ((char *)path_to_file);
}
