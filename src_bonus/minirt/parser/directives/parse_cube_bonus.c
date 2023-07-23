/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cube.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouba <aderouba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 16:38:48 by tdubois           #+#    #+#             */
/*   Updated: 2023/07/17 17:09:16 by aderouba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt/parser/parser_bonus.h"

#include "libft/libft.h"

#include "minirt/app/scene/scene_bonus.h"
#include "minirt/app/app_config_bonus.h"

static t_error	check_axis(
					t_parser_state *state,
					t_cube *const cube);

t_error	parse_cube(
			t_parser_state *state)
{
	t_object		obj;
	t_cube *const	cube = &obj.value.as_cube;

	ft_bzero(&obj, sizeof(t_object));
	if (parse_field(state, &g_position, &cube->pos) == FAILURE
		|| parse_field(state, &g_direction, &cube->x_axis) == FAILURE
		|| parse_field(state, &g_direction, &cube->y_axis) == FAILURE
		|| parse_field(state, &g_diameter, &cube->witdh) == FAILURE
		|| parse_field(state, &g_diameter, &cube->height) == FAILURE
		|| parse_field(state, &g_diameter, &cube->depth) == FAILURE
		|| parse_field(state, &g_color, &obj.color) == FAILURE)
		return (FAILURE);
	if (vec3_dot(&cube->x_axis, &cube->y_axis) != 0.0f)
	{
		return (FAILURE);
	}
	obj.type = OBJ_CUBE;
	obj.texture = NULL;
	obj.color_type = C_COLOR;
	obj.normal_map = NULL;
	obj.opacity = g_cube_default_opacity;
	obj.reflection = g_cube_default_reflection;
	obj.density = g_cube_default_density;
	return (scene_add_object(state->scene, &obj));
}

t_error	parse_cube_checkerboard(
			t_parser_state *state)
{
	t_object		obj;
	t_cube *const	cube = &obj.value.as_cube;

	ft_bzero(&obj, sizeof(t_object));
	if (parse_field(state, &g_position, &cube->pos) == FAILURE
		|| parse_field(state, &g_direction, &cube->x_axis) == FAILURE
		|| parse_field(state, &g_direction, &cube->y_axis) == FAILURE
		|| parse_field(state, &g_diameter, &cube->witdh) == FAILURE
		|| parse_field(state, &g_diameter, &cube->height) == FAILURE
		|| parse_field(state, &g_diameter, &cube->depth) == FAILURE)
		return (FAILURE);
	if (vec3_dot(&cube->x_axis, &cube->y_axis) != 0.0f)
	{
		return (FAILURE);
	}
	obj.type = OBJ_CUBE;
	obj.texture = NULL;
	obj.color = (t_color){0};
	obj.color_type = C_CHECKBOARD;
	obj.normal_map = NULL;
	obj.opacity = g_cube_default_opacity;
	obj.reflection = g_cube_default_reflection;
	obj.density = g_cube_default_density;
	return (scene_add_object(state->scene, &obj));
}

t_error	parse_cube_texture(
			t_parser_state *state)
{
	t_object		obj;
	t_cube *const	cube = &obj.value.as_cube;

	ft_bzero(&obj, sizeof(t_object));
	if (parse_field(state, &g_position, &cube->pos) == FAILURE
		|| parse_field(state, &g_direction, &cube->x_axis) == FAILURE
		|| parse_field(state, &g_direction, &cube->y_axis) == FAILURE
		|| parse_field(state, &g_diameter, &cube->witdh) == FAILURE
		|| parse_field(state, &g_diameter, &cube->height) == FAILURE
		|| parse_field(state, &g_diameter, &cube->depth) == FAILURE
		|| parse_field(state, &g_png, &obj.texture) == FAILURE)
		return (FAILURE);
	if (vec3_dot(&cube->x_axis, &cube->y_axis) != 0.0f)
	{
		return (FAILURE);
	}
	obj.type = OBJ_CUBE;
	obj.color = (t_color){0};
	obj.color_type = C_TEXTURE;
	obj.normal_map = NULL;
	obj.opacity = g_cube_default_opacity;
	obj.reflection = g_cube_default_reflection;
	obj.density = g_cube_default_density;
	return (scene_add_object(state->scene, &obj));
}

t_error	parse_cube_texture_and_normal(
			t_parser_state *state)
{
	t_object		obj;
	t_cube *const	cube = &obj.value.as_cube;

	ft_bzero(&obj, sizeof(t_object));
	if (parse_field(state, &g_position, &cube->pos) == FAILURE
		|| parse_field(state, &g_direction, &cube->x_axis) == FAILURE
		|| parse_field(state, &g_direction, &cube->y_axis) == FAILURE
		|| check_axis(state, cube) == FAILURE
		|| parse_field(state, &g_diameter, &cube->witdh) == FAILURE
		|| parse_field(state, &g_diameter, &cube->height) == FAILURE
		|| parse_field(state, &g_diameter, &cube->depth) == FAILURE
		|| parse_field(state, &g_png, &obj.texture) == FAILURE)
		return (FAILURE);
	if (parse_field(state, &g_png, &obj.normal_map) == FAILURE)
	{
		mlx_delete_texture(obj.texture);
		return (FAILURE);
	}
	obj.type = OBJ_CUBE;
	obj.color = (t_color){0};
	obj.color_type = C_TEXTURE;
	obj.opacity = g_cube_default_opacity;
	obj.reflection = g_cube_default_reflection;
	obj.density = g_cube_default_density;
	return (scene_add_object(state->scene, &obj));
}

static t_error	check_axis(
					t_parser_state *state,
					t_cube *const cube)
{
	if (vec3_dot(&cube->x_axis, &cube->y_axis) != 0.0f)
	{
		put_field_error(state, state->tok_start, "Invalid axis");
		return (FAILURE);
	}
	return (SUCCESS);
}
