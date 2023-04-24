/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_ambient_light.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdubois <tdubois@student.42angouleme.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 16:12:44 by tdubois           #+#    #+#             */
/*   Updated: 2023/04/18 17:14:57 by tdubois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt/parser/parser.h>
#include <minirt/scene/scene.h>
#include <libft/libft.h>
#include <stdio.h>
#include <stddef.h>

//############################################################################//
//#### DECLARATIONS ##########################################################//

t_parsing_error			parse_ambient_light(
							t_line_info const *line_info,
							char *line,
							t_scene *ret_scene);

static t_parsing_error	_assert_only_one_ambient_light(
							t_line_info const *line_info,
							t_scene *scene);

//############################################################################//
//#### DEFINITIONS ###########################################################//

t_parsing_error	parse_ambient_light(
							t_line_info const *line_info,
							char *line,
							t_scene *ret_scene)
{
	t_light			light;
	t_field const	fields[] = {
	{"brightness", &light.brightness, parse_brightness},
	{"color", &light.color, parse_color},
	{0}
	};

	if (_assert_only_one_ambient_light(line_info, ret_scene) == PARSING_FAILURE)
		return (PARSING_FAILURE);
	light = (t_light){0};
	if (parse_fields(line_info, line, fields) == PARSING_FAILURE)
		return (PARSING_FAILURE);
	ret_scene->ambient_lightning = ft_memdup(&light, sizeof(t_light));
	if (ret_scene->ambient_lightning == NULL)
		return (PARSING_FAILURE);
	return (PARSING_SUCCESS);
}

static t_parsing_error	_assert_only_one_ambient_light(
							t_line_info const *line_info,
							t_scene *scene)
{
	if (scene->ambient_lightning != NULL)
	{
		printf(g_too_many_ambient_lightning_directives_error,
			line_info->basename, line_info->line_nbr, line_info->line);
		return (PARSING_FAILURE);
	}
	return (PARSING_SUCCESS);
}
