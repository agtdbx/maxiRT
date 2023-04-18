/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_scene_file.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdubois <tdubois@student.42angouleme.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 10:08:33 by tdubois           #+#    #+#             */
/*   Updated: 2023/04/18 15:29:06 by tdubois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt/parser/parser.h>
#include <libft/libft.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <stdio.h>
#include <fcntl.h>

//############################################################################//
//#### DECLARATIONS ##########################################################//

t_parsing_error			parse_scene_file(
							char const *path_to_file,
							t_scene *ret_scene);

static t_parsing_error	loc_check_filename_format(
							char const *path_to_file);

static t_parsing_error	loc_open_file(
							char const *path_to_file,
							int	*ret_fd);

//############################################################################//
//#### DEFINITIONS ###########################################################//

t_parsing_error	parse_scene_file(
					char const *path_to_file,
					t_scene *ret_scene)
{
	int				fd;
	t_parsing_error	err;

	*ret_scene = (t_scene){0};
	if (loc_check_filename_format(path_to_file) == PARSING_FAILURE)
		return (PARSING_FAILURE);
	if (loc_open_file(path_to_file, &fd) == PARSING_FAILURE)
		return (PARSING_FAILURE);
	err = parse_lines(fd, path_to_file, ret_scene);
	if (err != PARSING_FAILURE && ret_scene->camera == NULL)
	{
		printf(g_missing_camera_error_msg, ft_basename(path_to_file));
		err = PARSING_FAILURE;
	}
	if (err == PARSING_FAILURE)
		scene_del(ret_scene);
	close(fd);
	return (err);
}

static t_parsing_error	loc_check_filename_format(
							char const *path_to_file)
{
	char const *const	basename = ft_basename(path_to_file);

	if (ft_strlen(basename) == 0)
	{
		printf(g_empty_filename_error_msg, path_to_file);
		return (PARSING_FAILURE);
	}
	if (ft_strendswith(basename, ".rt") == false)
	{
		printf(g_filename_extension_error_msg, path_to_file);
		return (PARSING_FAILURE);
	}
	if (ft_strlen(basename) <= 3)
	{
		printf(g_filename_too_short_error_msg, path_to_file);
		return (PARSING_FAILURE);
	}
	return (PARSING_SUCCESS);
}

static t_parsing_error	loc_open_file(
							char const *path_to_file,
							int	*ret_fd)
{
	*ret_fd = open(path_to_file, O_RDONLY);
	if (*ret_fd == -1)
	{
		printf(g_file_opening_error_msg, path_to_file, strerror(errno));
		return (PARSING_FAILURE);
	}
	if (read(*ret_fd, NULL, 0) == -1)
	{
		printf(g_file_opening_error_msg, path_to_file, strerror(errno));
		perror(NULL);
		close (*ret_fd);
		return (PARSING_FAILURE);
	}
	return (PARSING_SUCCESS);
}
