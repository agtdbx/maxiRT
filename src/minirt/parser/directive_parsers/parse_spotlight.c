/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_spotlight.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdubois <tdubois@student.42angouleme.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 14:39:36 by tdubois           #+#    #+#             */
/*   Updated: 2023/04/18 15:30:31 by tdubois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt/parser/parser.h>
#include <minirt/scene/scene.h>
#include <libft/libft.h>
#include <stdio.h>
#include <stddef.h>

//############################################################################//
//#### DECLARATIONS ##########################################################//

t_parsing_error			parse_spotlight(
							t_line_info const *line_info,
							char *line,
							t_scene *ret_scene);

static t_parsing_error	_assert_only_one_spotlight(
							t_line_info const *line_info,
							t_scene *scene);

//############################################################################//
//#### DEFINITIONS ###########################################################//

t_parsing_error	parse_spotlight(
							t_line_info const *line_info,
							char *line,
							t_scene *ret_scene)
{
	t_light			light;
	t_field const	fields[] = {
	{"position", &light.pos, parse_position},
	{"brightness", &light.brightness, parse_brightness},
	{"color", &light.color, parse_color},
	{NULL, NULL, NULL}
	};

	if (_assert_only_one_spotlight(line_info, ret_scene) == PARSING_FAILURE)
		return (PARSING_FAILURE);
	light = (t_light){0};
	if (parse_fields(line_info, line, fields) == PARSING_FAILURE)
		return (PARSING_FAILURE);
	ret_scene->spotlights = ft_memdup(&light, sizeof(t_light));
	if (ret_scene->spotlights == NULL)
		return (PARSING_FAILURE);
	return (PARSING_SUCCESS);
}

static t_parsing_error	_assert_only_one_spotlight(
							t_line_info const *line_info,
							t_scene *scene)
{
	if (scene->spotlights != NULL)
	{
		printf(g_too_many_spotlights_error,
			line_info->basename, line_info->line_nbr, line_info->line);
		return (PARSING_FAILURE);
	}
	return (PARSING_SUCCESS);
}
