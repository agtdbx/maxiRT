/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdubois <tdubois@student.42angouleme.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 10:08:33 by tdubois           #+#    #+#             */
/*   Updated: 2023/06/09 15:25:07 by tdubois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt/parser/parser.h"

#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>

#include "libft/libft.h"

#include "minirt/app/scene/scene.h"

static t_error	_check_filename_format(
					char const *basename);
static t_error	_open_file(
					char const *path_to_file,
					int	*fd);

/**
 * Parses scene data structure from config file.
 * 
 * @param[in] path_to_file Path to config file
 * @param[out] scene Scene to fill up with parsed data
 * @returns SUCCESS or FAILURE whether parsing has has been succesful or not
 */
t_error	parse_file(
			char const *path_to_file,
			t_scene *scene)
{
	int					fd;
	char const *const	basename = ft_basename(path_to_file);

	*scene = (t_scene){0};
	if (!_check_filename_format(basename))
		return (FAILURE);
	if (!_open_file(path_to_file, &fd))
		return (FAILURE);
	if (!parse_lines(fd, basename, scene))
	{
		close(fd);
		scene_del(scene);
		return (FAILURE);
	}
	if (scene->camera == NULL)
	{
		close(fd);
		scene_del(scene);
		printf(g_file_err, basename, "Missing camera directive");
		return (FAILURE);
	}
	close (fd);
	return (SUCCESS);
}

/**
 * Private: Open file with error feedback
 * 
 * @param[in] path_to_file
 * @param[out] fd
 * @returns SUCCESS or FAILURE whether file has been opened or not
 */
static t_error	_open_file(
					char const *path_to_file,
					int	*fd)
{
	*fd = open(path_to_file, O_RDONLY);
	if (*fd == -1)
	{
		printf(g_file_err, path_to_file, strerror(errno));
		return (FAILURE);
	}
	if (read(*fd, NULL, 0) == -1)
	{
		printf(g_file_err, path_to_file, strerror(errno));
		perror(NULL);
		close (*fd);
		return (FAILURE);
	}
	return (SUCCESS);
}

/**
 * Private: Perform validation on filename format.
 * 1. Checks for extension
 * 2. Empty filename
 * 3. Extension only filename
 * 
 * @param[in] basename Basename of config file
 * @returns SUCCESS or FAILURE whether file has been opened or not
 */
static t_error	_check_filename_format(
					char const *basename)
{
	if (ft_strlen(basename) == 0)
	{
		printf(g_file_err, basename, "Invalid filename: Is empty");
		return (FAILURE);
	}
	if (ft_strendswith(basename, ".rt") == false)
	{
		printf(g_file_err, basename, "Invalid filename: Bad extension");
		return (FAILURE);
	}
	if (ft_strlen(basename) <= 3)
	{
		printf(g_file_err, basename, "Invalid filename: Is empty");
		return (FAILURE);
	}
	return (SUCCESS);
}
