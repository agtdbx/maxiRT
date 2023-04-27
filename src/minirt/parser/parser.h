/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdubois <tdubois@student.42angouleme.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 10:53:16 by tdubois           #+#    #+#             */
/*   Updated: 2023/04/27 15:47:27 by tdubois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include <minirt/parser/parser_int.h>

//**** PARSER DIRECTIVES *****************************************************//

static const t_directive	g_directives[] = {
{
	.identifier = "C",
	.usage = "C <position> <orientation vector> <fov>",
	.callback = parse_camera,
},
// {
// 	.identifier = "A",
// 	.usage = "A <brightness> <color>",
// 	.callback = parse_ambient_light,
// },
// {
// 	.identifier = "Tr",
// 	.usage = "Tr <position> <position> <position> <color>",
// 	.callback = parse_triangle,
// },
};

//**** PARSER FIELDS *********************************************************//

static const t_field		g_fov = {
	.identifier = "fov",
	.usage = "Horizontal field of view in degrees in range [0,180]",
	.callback = parse_fov
};

static const t_field		g_brightness = {
	.identifier = "brightness",
	.usage = "lighting ratio in range [0.0,1.0]",
	.callback = parse_brightness
};

static const t_field		g_position = {
	.identifier = "position",
	.usage = "x,y,z coordinates",
	.callback = parse_vec3
};

static const t_field		g_direction = {
	.identifier = "direction",
	.usage = "3d normalized vector x,y,z",
	.callback = parse_vec3
};

//**** PARSER ERRORS *********************************************************//

//---- filename errors -------------------------------------------------------//

static const char			g_file_err[] = \
	"Error"																"\n"
	"<%s>: %s"															"\n";

#endif//PARSER_H
