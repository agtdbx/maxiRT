/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdubois <tdubois@student.42angouleme.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 10:08:33 by tdubois           #+#    #+#             */
/*   Updated: 2023/04/24 17:46:06 by tdubois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt/parser/parser.h>
#include <libft/libft.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>//TODO

//############################################################################//
//#### DECLARATIONS ##########################################################//

t_parser_error			parse_file(
							char const *path_to_file,
							t_scene *ret_scene);

static t_parser_error	_check_filename_format(
							char const *basename);

static t_parser_error	_open_file(
							char const *path_to_file,
							int	*fd);

//############################################################################//
//#### DEFINITIONS ###########################################################//

t_parser_error	parse_file(
					char const *path_to_file,
					t_scene *scene)
{
	int					fd;
	char const *const	basename = ft_basename(path_to_file);

	*scene = (t_scene){0};
	if (!_check_filename_format(basename))
		return (PARSING_FAILURE);
	if (!_open_file(path_to_file, &fd))
		return (PARSING_FAILURE);
	if (!parse_lines(fd, basename, scene))
	{
		close(fd);
		scene_del(scene);
		return (PARSING_FAILURE);
	}
	if (scene->camera == NULL)
	{
		close(fd);
		scene_del(scene);
		printf(g_file_err, basename, "Missing camera directive");
		return (PARSING_FAILURE);
	}
	close (fd);
	return (PARSING_SUCCESS);
}

static t_parser_error	_check_filename_format(
							char const *basename)
{
	if (ft_strlen(basename) == 0)
	{
		printf(g_file_err, basename, "Invalid filename: Is empty");
		return (PARSING_FAILURE);
	}
	if (ft_strendswith(basename, ".rt") == false)
	{
		printf(g_file_err, basename, "Invalid filename: Bad extension");
		return (PARSING_FAILURE);
	}
	if (ft_strlen(basename) <= 3)
	{
		printf(g_file_err, basename, "Invalid filename: Is empty");
		return (PARSING_FAILURE);
	}
	return (PARSING_SUCCESS);
}


/** 
 * Open file with error feedback
 * 
 * @param[in] path_to_file
 * @param[out] fd
 * @returns PARSING_SUCCESS or PARSING_FAILURE whether file has been
 * opened or not
 */
static t_parser_error	_open_file(
							char const *path_to_file,
							int	*fd)
{
	*fd = open(path_to_file, O_RDONLY);
	if (*fd == -1)
	{
		printf(g_file_err, path_to_file, strerror(errno));
		return (PARSING_FAILURE);
	}
	if (read(*fd, NULL, 0) == -1)
	{
		printf(g_file_err, path_to_file, strerror(errno));
		perror(NULL);
		close (*fd);
		return (PARSING_FAILURE);
	}
	return (PARSING_SUCCESS);
}
