/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdubois <tdubois@student.42angouleme.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 22:58:42 by tdubois           #+#    #+#             */
/*   Updated: 2023/04/24 10:53:06 by tdubois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt/app/app.h>
#include <minirt/scene/scene.h>
#include <minirt/parser/parser.h>
#include <MLX42/MLX42.h>

#include <stdio.h>
#include <stdlib.h>

static const char	g_argc_error_msg[] = \
	"Error"								"\n"
	""									"\n"
	"Expected one argument"				"\n"
	"Usage: minirt <path/to/scene.rt>"	"\n";

int	main(int argc, char *argv[])
{
	mlx_errno_t	err;
	t_scene		scene;

	if (argc != 2)
	{
		printf(g_argc_error_msg);
		return (EXIT_FAILURE);
	}
	if (parse_file(argv[1], &scene) == PARSING_FAILURE)
		return (EXIT_FAILURE);
	err = app_start();//pass scene that has been parsed out
	//destroy scene
	return (err);
}
