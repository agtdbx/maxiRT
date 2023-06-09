/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdubois <tdubois@student.42angouleme.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 22:58:42 by tdubois           #+#    #+#             */
/*   Updated: 2023/06/09 15:22:48 by tdubois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

#include "MLX42/MLX42.h"

#include "minirt/app/app.h"
#include "minirt/app/scene/scene.h"
#include "minirt/parser/parser.h"

static const char	g_argc_error_msg[] = \
	"Error"								"\n"
	"Expected one argument"				"\n"
	"Usage: minirt <path/to/scene.rt>"	"\n";

int	main(int argc, char *argv[])
{
	t_scene	scene;

	if (argc != 2)
	{
		printf(g_argc_error_msg);
		return (EXIT_FAILURE);
	}
	if (parse_file(argv[1], &scene) == FAILURE)
	{
		return (EXIT_FAILURE);
	}
	if (app_start(&scene) == FAILURE)
	{
		scene_del(&scene);
		return (EXIT_FAILURE);
	}
	scene_del(&scene);
	return (EXIT_SUCCESS);
}
