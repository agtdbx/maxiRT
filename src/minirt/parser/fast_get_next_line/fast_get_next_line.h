/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fast_get_next_line.h                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auguste <auguste@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 18:04:25 by auguste           #+#    #+#             */
/*   Updated: 2024/03/17 18:17:33 by auguste          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FAST_GET_NEXT_LINE_H
# define FAST_GET_NEXT_LINE_H

# include "libft/libft.h"

# define FGNL_BUFFER_SIZE 128

char	*fast_get_next_line(
			int fd);

int		_fgnl_copy_line_in_buffer(
				char buffer[FGNL_BUFFER_SIZE],
				char **line,
				int i);
int		_fgnl_copy_read_line_in_line(
				char buffer[FGNL_BUFFER_SIZE],
				char read_buffer[FGNL_BUFFER_SIZE],
				char **line,
				int i);
void	_fgnl_extend_str(
				char **str,
				char *to_add);

#endif
