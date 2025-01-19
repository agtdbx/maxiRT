/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_paraboloid.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gugus <gugus@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 22:49:47 by damien            #+#    #+#             */
/*   Updated: 2025/01/19 15:11:52 by gugus            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42/MLX42.h"
#include "minirt/parser/parser.h"

#include "libft/libft.h"

t_error	parse_paraboloid(
			t_parser_state *state)
{
	t_object			obj;
	t_paraboloid *const	paraboloid = &obj.value.as_paraboloid;

	ft_bzero(&obj, sizeof(t_object));
	if (parse_field(state, &g_position, &paraboloid->pos) == FAILURE
		|| parse_field(state, &g_direction, &paraboloid->dir) == FAILURE
		|| parse_field(state, &g_diameter, &paraboloid->k) == FAILURE
		|| parse_field(state, &g_color, &obj.color) == FAILURE)
		return (FAILURE);
	obj.type = OBJ_PARABOLOID;
	obj.texture = NULL;
	obj.color_type = C_COLOR;
	obj.normal_map = NULL;
	obj.opacity = g_paraboloid_default_opacity;
	obj.reflection = g_paraboloid_default_reflection;
	obj.density = g_paraboloid_default_density;
	return (scene_add_object(state->scene, &obj));
}

t_error	parse_paraboloid_checkerboard(
			t_parser_state *state)
{
	t_object			obj;
	t_paraboloid *const	paraboloid = &obj.value.as_paraboloid;

	ft_bzero(&obj, sizeof(t_object));
	if (parse_field(state, &g_position, &paraboloid->pos) == FAILURE
		|| parse_field(state, &g_direction, &paraboloid->dir) == FAILURE
		|| parse_field(state, &g_diameter, &paraboloid->k) == FAILURE)
		return (FAILURE);
	obj.type = OBJ_PARABOLOID;
	obj.texture = NULL;
	obj.color_type = C_CHECKBOARD;
	obj.normal_map = NULL;
	obj.opacity = g_paraboloid_default_opacity;
	obj.reflection = g_paraboloid_default_reflection;
	obj.density = g_paraboloid_default_density;
	return (scene_add_object(state->scene, &obj));
}

t_error	parse_paraboloid_sinusoide(
			t_parser_state *state)
{
		t_object			obj;
	t_paraboloid *const	paraboloid = &obj.value.as_paraboloid;

	ft_bzero(&obj, sizeof(t_object));
	if (parse_field(state, &g_position, &paraboloid->pos) == FAILURE
		|| parse_field(state, &g_direction, &paraboloid->dir) == FAILURE
		|| parse_field(state, &g_diameter, &paraboloid->k) == FAILURE)
		return (FAILURE);
	obj.type = OBJ_PARABOLOID;
	obj.texture = NULL;
	obj.color_type = C_SINUSOIDE;
	obj.normal_map = NULL;
	obj.opacity = g_paraboloid_default_opacity;
	obj.reflection = g_paraboloid_default_reflection;
	obj.density = g_paraboloid_default_density;
	return (scene_add_object(state->scene, &obj));
}

t_error	parse_paraboloid_perlin_noise(
			t_parser_state *state)
{
	t_object			obj;
	t_paraboloid *const	paraboloid = &obj.value.as_paraboloid;

	ft_bzero(&obj, sizeof(t_object));
	if (parse_field(state, &g_position, &paraboloid->pos) == FAILURE
		|| parse_field(state, &g_direction, &paraboloid->dir) == FAILURE
		|| parse_field(state, &g_diameter, &paraboloid->k) == FAILURE)
		return (FAILURE);
	obj.type = OBJ_PARABOLOID;
	obj.texture = NULL;
	obj.color_type = C_PERLIN_NOISE;
	obj.normal_map = NULL;
	obj.opacity = g_paraboloid_default_opacity;
	obj.reflection = g_paraboloid_default_reflection;
	obj.density = g_paraboloid_default_density;
	return (scene_add_object(state->scene, &obj));
}

t_error	parse_paraboloid_texture(
			t_parser_state *state)
{
	t_object			obj;
	t_paraboloid *const	paraboloid = &obj.value.as_paraboloid;

	ft_bzero(&obj, sizeof(t_object));
	if (parse_field(state, &g_position, &paraboloid->pos) == FAILURE
		|| parse_field(state, &g_direction, &paraboloid->dir) == FAILURE
		|| parse_field(state, &g_diameter, &paraboloid->k) == FAILURE
		|| parse_field(state, &g_png, &obj.texture) == FAILURE)
		return (FAILURE);
	obj.type = OBJ_PARABOLOID;
	obj.color = (t_color){0};
	obj.color_type = C_TEXTURE;
	obj.normal_map = NULL;
	obj.opacity = g_paraboloid_default_opacity;
	obj.reflection = g_paraboloid_default_reflection;
	obj.density = g_paraboloid_default_density;
	return (scene_add_object(state->scene, &obj));
}

t_error	parse_paraboloid_texture_and_normal(
			t_parser_state *state)
{
	t_object			obj;
	t_paraboloid *const	paraboloid = &obj.value.as_paraboloid;

	ft_bzero(&obj, sizeof(t_object));
	if (parse_field(state, &g_position, &paraboloid->pos) == FAILURE
		|| parse_field(state, &g_direction, &paraboloid->dir) == FAILURE
		|| parse_field(state, &g_diameter, &paraboloid->k) == FAILURE
		|| parse_field(state, &g_png, &obj.texture) == FAILURE)
		return (FAILURE);
	if (parse_field(state, &g_png, &obj.normal_map) == FAILURE)
	{
		mlx_delete_texture(obj.texture);
		return (FAILURE);
	}
	obj.type = OBJ_PARABOLOID;
	obj.color = (t_color){0};
	obj.color_type = C_TEXTURE;
	obj.opacity = g_paraboloid_default_opacity;
	obj.reflection = g_paraboloid_default_reflection;
	obj.density = g_paraboloid_default_density;
	return (scene_add_object(state->scene, &obj));
}
