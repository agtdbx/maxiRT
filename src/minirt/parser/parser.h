/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auguste <auguste@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 10:53:16 by tdubois           #+#    #+#             */
/*   Updated: 2024/03/17 13:02:49 by auguste          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include <minirt/parser/parser_int.h>

//**** PARSER DIRECTIVES *****************************************************//

static const t_directive	g_directives[] = {
{
	.identifier = "S",
	.usage = "S <texture path>",
	.callback = parse_skybox,
},
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
	.identifier = "li",
	.usage = "li <position> <brightness> <color>",
	.callback = parse_spotlight,
},
{
	.identifier = "sp",
	.usage = "sp <position> <diameter> <color>",
	.callback = parse_sphere,
},
{
	.identifier = "sp-ck",
	.usage = "sp-ck <position> <diameter>",
	.callback = parse_sphere_checkerboard,
},
{
	.identifier = "sp-sn",
	.usage = "sp-sn <position> <diameter>",
	.callback = parse_sphere_sinusoide,
},
{
	.identifier = "sp-pn",
	.usage = "sp-pn <position> <diameter>",
	.callback = parse_sphere_perlin_noise,
},
{
	.identifier = "sp-t",
	.usage = "sp-t <position> <diameter> <texture path>",
	.callback = parse_sphere_texture,
},
{
	.identifier = "sp-tn",
	.usage = "sp-tn <position> <diameter> <texture path> <normal map path>",
	.callback = parse_sphere_texture_and_normal,
},
{
	.identifier = "pl",
	.usage = "pl <position> <orientation vector> <color>",
	.callback = parse_plane,
},
{
	.identifier = "pl-ck",
	.usage = "pl-ck <position> <orientation vector>",
	.callback = parse_plane_checkerboard,
},
{
	.identifier = "pl-t",
	.usage = "pl-t <position> <orientation vector> "
	"<texture path>",
	.callback = parse_plane_texture,
},
{
	.identifier = "pl-tn",
	.usage = "pl-tn <position> <orientation vector> "
	"<texture path> <normal map path>",
	.callback = parse_plane_texture_and_normal,
},
{
	.identifier = "cy",
	.usage = "cy <position> <orientation vector> <diameter> <height> <color>",
	.callback = parse_cylinder,
},
{
	.identifier = "cy-ck",
	.usage = "cy-ck <position> <orientation vector> <diameter> <height>",
	.callback = parse_cylinder_checkerboard,
},
{
	.identifier = "cy-t",
	.usage = "cy-t <position> <orientation vector> <diameter> <height>"
	"<texture path>",
	.callback = parse_cylinder_texture,
},
{
	.identifier = "cy-tn",
	.usage = "cy-tn <position> <orientation vector> <diameter> <height>"
	"<texture path> <normal map path>",
	.callback = parse_cylinder_texture_and_normal,
},
{
	.identifier = "co",
	.usage = "co <position> <orientation vector> <diameter> <height> <color>",
	.callback = parse_cone,
},
{
	.identifier = "co-ck",
	.usage = "co-ck <position> <orientation vector> <diameter> <height>",
	.callback = parse_cone_checkerboard,
},
{
	.identifier = "co-t",
	.usage = "co-t <position> <orientation vector> <diameter> <height> "
	"<texture path>",
	.callback = parse_cone_texture,
},
{
	.identifier = "co-tn",
	.usage = "co-tn <position> <orientation vector> <diameter> <height> "
	"<texture path> <normal map path>",
	.callback = parse_cone_texture_and_normal,
},
{
	.identifier = "cu",
	.usage = "cu <position> <orientation x vector> <orientation y vector> "
	"<widht> <height> <depth> <color>",
	.callback = parse_cube,
},
{
	.identifier = "cu-ck",
	.usage = "cu-ck <position> <orientation x vector> <orientation y vector> "
	"<widht> <height> <depth>",
	.callback = parse_cube_checkerboard,
},
{
	.identifier = "cu-t",
	.usage = "cu-t <position> <orientation x vector> <orientation y vector> "
	"<widht> <height> <depth> <texture path>",
	.callback = parse_cube_texture,
},
{
	.identifier = "cu-tn",
	.usage = "cu-tn <position> <orientation x vector> <orientation y vector> "
	"<widht> <height> <depth> <texture path> <normal map path>",
	.callback = parse_cube_texture_and_normal,
},
{
	.identifier = "tr",
	.usage = "tr <point> <point> <point> <color>",
	.callback = parse_triangle,
},
{
	.identifier = "tr-ck",
	.usage = "tr <point> <point> <point>",
	.callback = parse_triangle_checkerboard,
},
{
	.identifier = "tr-t",
	.usage = "tr <point> <point> <point> <texture path>",
	.callback = parse_triangle_texture,
},
{
	.identifier = "tr-tn",
	.usage = "tr <point> <point> <point> <texture path> <normal map path>",
	.callback = parse_triangle_texture_and_normal,
},
{
	.identifier = "ob",
	.usage = "ob <position> <orientation x vector> <orientation y vector> "
	"<size> <obj file path> <color>",
	.callback = parse_object_file,
},
{
	.identifier = "ob-ck",
	.usage = "ob <position> <orientation x vector> <orientation y vector> "
	"<size> <obj file path>",
	.callback = parse_object_file_checkerboard,
},
{
	.identifier = "ob-t",
	.usage = "ob <position> <orientation x vector> <orientation y vector> "
	"<size> <obj file path> <texture path>",
	.callback = parse_object_file_texture,
},
{
	.identifier = "ob-tn",
	.usage = "ob <position> <orientation x vector> <orientation y vector> "
	"<size> <obj file path> <texture path> <normal map path>",
	.callback = parse_object_file_texture_and_normal,
},
{
	.identifier = "#",
	.usage = "a comment !",
	.callback = parse_comment,
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

static const t_field		g_png = {
	.identifier = "png",
	.usage = "png file to load",
	.callback = parse_png,
};

static const t_field		g_objf = {
	.identifier = "objf",
	.usage = ".obj file to load",
	.callback = parse_dot_obj_file,
};

static const t_field		g_empty = {
	.identifier = "empty",
	.usage = "this field is empty",
	.callback = NULL,
};

//**** PARSER ERRORS *********************************************************//

//---- filename errors -------------------------------------------------------//

static const char			g_file_err[] = \
	"Error"																"\n"
	"<%s>: %s"															"\n";

#endif//PARSER_H
