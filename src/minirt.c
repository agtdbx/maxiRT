/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdubois <tdubois@student.42angouleme.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 22:58:42 by tdubois           #+#    #+#             */
/*   Updated: 2023/04/14 00:33:11 by tdubois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt/app/app.h>

#include <stdio.h>
#include <stdlib.h>

#include "MLX42/MLX42.h"

static const char	g_main_usage[] = \
	"Error"								"\n"
	""									"\n"
	"Usage: minirt <path/to/scene.rt>"	"\n";

int	main(int argc, char *argv[])
{
	mlx_errno_t	err;
	//declare scene

	(void) argv;
	if (argc != 2)
	{
		printf(g_main_usage);
		return (EXIT_FAILURE);
	}
	// if (parse_scene_file(argv[1], &app.scene) == PARSING_FAILURE)
	// 	return (EXIT_FAILURE);
	err = app_start();//pass scene that has been parsed out
	//destroy scene
	return (err);
}
