/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_dot_file_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auguste <auguste@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 11:47:03 by auguste           #+#    #+#             */
/*   Updated: 2024/03/16 16:46:55 by auguste          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt/parser/dot_obj_file/dot_obj_file_bonus.h"
#include "libft/libft.h"
#include <stdlib.h>
#include <stdio.h>

static bool	parse_line(char *line, t_parse_dot_struct *parse_dot_struct);
static bool	parse_vertice(char **save_ptr, t_parse_dot_struct *parse_dot_struct);
static bool	parse_face(char **save_ptr, t_parse_dot_struct *parse_dot_struct);

/* Function to parse a .obj file.
 * @param fd The fd of the file to read
 * @param parse_dot_struct The struct for obj file parsing
 * @return PARSE_DOT_FILE_SUCCESS(-1) if the parsing work as well,
 *  number of the error line instead
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
	char	*save_ptr;
	char	*tok;

	tok = ft_strtok_r(line, " ", &save_ptr);
	//printf("tok |%s| : line %s", tok, line);
	// In case of vertice
	if (ft_strcmp(tok, "v") == 0)
		return (parse_vertice(&save_ptr, parse_dot_struct));
	// In case of face
	if (ft_strcmp(tok, "f") == 0)
		return (parse_face(&save_ptr, parse_dot_struct));
	//In any other case, skip the line
	return (true);
}


static bool	parse_vertice(char **save_ptr, t_parse_dot_struct *parse_dot_struct)
{
	char	*tok;
	char	*endptr;
	float	x;
	float	y;
	float	z;

	// get x
	tok = ft_strtok_r(NULL, " \n", save_ptr);
	if (tok == NULL)
		return (false);
	x = ft_strtof(tok, &endptr);
	if (endptr[0] != '\0')
		return (false);

	// get y
	tok = ft_strtok_r(NULL, " \n", save_ptr);
	if (tok == NULL)
		return (false);
	y = ft_strtof(tok, &endptr);
	if (endptr[0] != '\0')
		return (false);

	// get z
	tok = ft_strtok_r(NULL, " \n", save_ptr);
	if (tok == NULL)
		return (false);
	z = ft_strtof(tok, &endptr);
	if (endptr[0] != '\0')
		return (false);

	// Check if the end is not empty
	tok = ft_strtok_r(NULL, " ", save_ptr);
	if (tok != NULL)
		return (false);

	parse_dot_struct_add_vertice(parse_dot_struct, x, y, z);
	return (true);
}


static bool	parse_face(char **save_ptr, t_parse_dot_struct *parse_dot_struct)
{
	char	*tok;
	char	*number_str;
	char	*save_ptr2;
	char	*endptr;
	int		p1;
	int		p2;
	int		p3;

	// get p1
	tok = ft_strtok_r(NULL, " \n", save_ptr);
	if (tok == NULL)
		return (false);
	number_str = ft_strtok_r(tok, "/", &save_ptr2);
	p1 = ft_strtoi(number_str, &endptr);
	if (endptr[0] != '\0')
		return (false);

	// get p2
	tok = ft_strtok_r(NULL, " \n", save_ptr);
	if (tok == NULL)
		return (false);
	number_str = ft_strtok_r(tok, "/", &save_ptr2);
	p2 = ft_strtof(number_str, &endptr);
	if (endptr[0] != '\0')
		return (false);

	// get p3
	tok = ft_strtok_r(NULL, " \n", save_ptr);
	if (tok == NULL)
		return (false);
	number_str = ft_strtok_r(tok, "/", &save_ptr2);
	p3 = ft_strtof(number_str, &endptr);
	if (endptr[0] != '\0')
		return (false);

	// Check if the end is not empty
	tok = ft_strtok_r(NULL, " ", save_ptr);
	if (tok != NULL)
		return (false);

	parse_dot_struct_add_face(parse_dot_struct, p1, p2, p3);
	return (true);
}
