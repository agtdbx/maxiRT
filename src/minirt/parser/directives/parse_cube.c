/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cube.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouba <aderouba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 16:38:48 by tdubois           #+#    #+#             */
/*   Updated: 2023/07/05 13:23:38 by aderouba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt/parser/parser.h"

#include "libft/libft.h"

#include "minirt/app/scene/scene.h"
#include "minirt/app/app_config.h"

t_error	parse_cube(
			t_parser_state *state)
{
	t_object	obj;
	t_cube	*const cube = &obj.value.as_cube;

	ft_bzero(&obj, sizeof(t_object));
	if (parse_field(state, &g_position, &cube->pos) == FAILURE
		|| parse_field(state, &g_direction, &cube->x_axis) == FAILURE
		|| parse_field(state, &g_direction, &cube->y_axis) == FAILURE
		|| parse_field(state, &g_diameter, &cube->witdh) == FAILURE
		|| parse_field(state, &g_diameter, &cube->height) == FAILURE
		|| parse_field(state, &g_diameter, &cube->depth) == FAILURE
		|| parse_field(state, &g_color, &obj.color) == FAILURE)
		return (FAILURE);
	// TODO Message erreur si les deux axes ne sont pas bon
	if (vec3_dot(&cube->x_axis, &cube->y_axis) != 0.0f)
		return (FAILURE);
	obj.type = OBJ_CUBE;
	obj.texture = NULL;
	// obj.texture = mlx_load_png("imgs/Stylized_Stone_texture.png");
	obj.color_type = C_COLOR;
	obj.normal_map = NULL;
	// obj.normal_map = mlx_load_png("imgs/Stylized_Stone_normal.png");
	obj.opacity = g_cube_default_opacity;
	obj.reflection = g_cube_default_reflection;
	obj.density = g_cube_default_density;
	return (scene_add_object(state->scene, &obj));
}
