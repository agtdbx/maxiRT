/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_dot_file_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auguste <auguste@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 11:47:03 by auguste           #+#    #+#             */
/*   Updated: 2024/03/16 12:39:20 by auguste          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt/parser/dot_obj_file/dot_obj_file_bonus.h"
#include "libft/libft.h"

static bool	parse_line(char *line, t_parse_dot_struct *parse_dot_struct);

/* Function to parse a .obj file
 * @param fd The fd of the file to read
 * @param parse_dot_struct The struct for obj file parsing
 * @return PARSE_DOT_FILE_SUCCESS(-1) if the parsing work as well, number of the error line instead
 */
int	parse_dot_file(int fd, t_parse_dot_struct *parse_dot_struct)
{
	char	*line;
	int		line_number;

	line = ft_gnl(fd);
	if (line == NULL)
		return (0);
	line_number = 0;
	while (line != NULL)
	{
		if (!parse_line(line, parse_dot_struct))
		{
			free(line);
			parse_dot_struct_free(parse_dot_struct);
			return (line_number);
		}
		free(line);
		line_number++;
		line = ft_gnl(fd);
	}
	return (PARSE_DOT_FILE_SUCCESS);
}


static bool	parse_line(char *line, t_parse_dot_struct *parse_dot_struct)
{

}
