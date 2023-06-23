/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouba <aderouba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 10:53:16 by tdubois           #+#    #+#             */
/*   Updated: 2023/06/23 14:01:45 by aderouba         ###   ########.fr       */
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
{
	.identifier = "A",
	.usage = "A <brightness> <color>",
	.callback = parse_ambient_light,
},
{
	.identifier = "L",
	.usage = "L <position> <brightness> <color>",
	.callback = parse_spotlight,
},
{
	.identifier = "sp",
	.usage = "sp <position> <diameter> <color>",
	.callback = parse_sphere,
},
{
	.identifier = "pl",
	.usage = "sp <position> <orientation vector> <color>",
	.callback = parse_plane,
},
{
	.identifier = "cy",
	.usage = "cy <position> <orientation vector> <diameter> <height> <color>",
	.callback = parse_cylinder,
},
{
	.identifier = "co",
	.usage = "co <position> <orientation vector> <diameter> <height> <color>",
	.callback = parse_cone,
},
};

//**** PARSER FIELDS *********************************************************//

static const t_field		g_fov = {
	.identifier = "fov",
	.usage = "Horizontal field of view in degrees in range [0,180]",
	.callback = parse_fov,
};

static const t_field		g_diameter = {
	.identifier = "diameter",
	.usage = "Object's diameter in range [0,+infty]",
	.callback = parse_diameter,
};

static const t_field		g_brightness = {
	.identifier = "brightness",
	.usage = "lighting ratio in range [0.0,1.0]",
	.callback = parse_brightness,
};

static const t_field		g_position = {
	.identifier = "position",
	.usage = "x,y,z coordinates",
	.callback = parse_vec3,
};

static const t_field		g_direction = {
	.identifier = "orientation vector",
	.usage = "3d normalized vector x,y,z",
	.callback = parse_direction,
};

static const t_field		g_color = {
	.identifier = "color",
	.usage = "R,G,B colors in range [0-255]",
	.callback = parse_color,
};

//**** PARSER ERRORS *********************************************************//

//---- filename errors -------------------------------------------------------//

static const char			g_file_err[] = \
	"Error"																"\n"
	"<%s>: %s"															"\n";

#endif//PARSER_H
