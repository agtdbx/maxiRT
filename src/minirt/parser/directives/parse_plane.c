/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_plane.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gugus <gugus@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 16:38:48 by tdubois           #+#    #+#             */
/*   Updated: 2025/01/16 04:16:27 by gugus            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt/parser/parser.h"

#include "libft/libft.h"

#include "minirt/app/scene/scene.h"
#include "minirt/app/app_config.h"

t_error	parse_plane(
			t_parser_state *state)
{
	t_object		obj;
	t_plane *const	plane = &obj.value.as_plane;

	ft_bzero(&obj, sizeof(t_object));
	if (parse_field(state, &g_position, &plane->pos) == FAILURE
		|| parse_field(state, &g_direction, &plane->normal) == FAILURE
		|| parse_field(state, &g_color, &obj.color) == FAILURE)
		return (FAILURE);
	obj.type = OBJ_PLANE;
	obj.texture = NULL;
	obj.color_type = C_COLOR;
	obj.normal_map = NULL;
	obj.opacity = g_plane_default_opacity;
	obj.reflection = g_plane_default_reflection;
	obj.density = g_plane_default_density;
	return (scene_add_object(state->scene, &obj));
}

t_error	parse_plane_checkerboard(
			t_parser_state *state)
{
	t_object		obj;
	t_plane *const	plane = &obj.value.as_plane;

	ft_bzero(&obj, sizeof(t_object));
	if (parse_field(state, &g_position, &plane->pos) == FAILURE
		|| parse_field(state, &g_direction, &plane->normal) == FAILURE)
		return (FAILURE);
	obj.type = OBJ_PLANE;
	obj.texture = NULL;
	obj.color = (t_color){0};
	obj.color_type = C_CHECKBOARD;
	obj.normal_map = NULL;
	obj.opacity = g_plane_default_opacity;
	obj.reflection = g_plane_default_reflection;
	obj.density = g_plane_default_density;
	return (scene_add_object(state->scene, &obj));
}

t_error	parse_plane_sinusoide(
			t_parser_state *state)
{
	t_object		obj;
	t_plane *const	plane = &obj.value.as_plane;

	ft_bzero(&obj, sizeof(t_object));
	if (parse_field(state, &g_position, &plane->pos) == FAILURE
		|| parse_field(state, &g_direction, &plane->normal) == FAILURE)
		return (FAILURE);
	obj.type = OBJ_PLANE;
	obj.texture = NULL;
	obj.color = (t_color){0};
	obj.color_type = C_SINUSOIDE;
	obj.normal_map = NULL;
	obj.opacity = g_plane_default_opacity;
	obj.reflection = g_plane_default_reflection;
	obj.density = g_plane_default_density;
	return (scene_add_object(state->scene, &obj));
}

t_error	parse_plane_perlin_noise(
			t_parser_state *state)
{
	t_object		obj;
	t_plane *const	plane = &obj.value.as_plane;

	ft_bzero(&obj, sizeof(t_object));
	if (parse_field(state, &g_position, &plane->pos) == FAILURE
		|| parse_field(state, &g_direction, &plane->normal) == FAILURE)
		return (FAILURE);
	obj.type = OBJ_PLANE;
	obj.texture = NULL;
	obj.color = (t_color){0};
	obj.color_type = C_PERLIN_NOISE;
	obj.normal_map = NULL;
	obj.opacity = g_plane_default_opacity;
	obj.reflection = g_plane_default_reflection;
	obj.density = g_plane_default_density;
	return (scene_add_object(state->scene, &obj));
}

t_error	parse_plane_texture(
			t_parser_state *state)
{
	t_object		obj;
	t_plane *const	plane = &obj.value.as_plane;

	ft_bzero(&obj, sizeof(t_object));
	if (parse_field(state, &g_position, &plane->pos) == FAILURE
		|| parse_field(state, &g_direction, &plane->normal) == FAILURE
		|| parse_field(state, &g_png, &obj.texture) == FAILURE)
		return (FAILURE);
	obj.type = OBJ_PLANE;
	obj.color = (t_color){0};
	obj.color_type = C_TEXTURE;
	obj.normal_map = NULL;
	obj.opacity = g_plane_default_opacity;
	obj.reflection = g_plane_default_reflection;
	obj.density = g_plane_default_density;
	return (scene_add_object(state->scene, &obj));
}

t_error	parse_plane_texture_and_normal(
			t_parser_state *state)
{
	t_object		obj;
	t_plane *const	plane = &obj.value.as_plane;

	ft_bzero(&obj, sizeof(t_object));
	if (parse_field(state, &g_position, &plane->pos) == FAILURE
		|| parse_field(state, &g_direction, &plane->normal) == FAILURE
		|| parse_field(state, &g_png, &obj.texture) == FAILURE)
		return (FAILURE);
	if (parse_field(state, &g_png, &obj.normal_map) == FAILURE)
	{
		mlx_delete_texture(obj.texture);
		return (FAILURE);
	}
	obj.type = OBJ_PLANE;
	obj.color = (t_color){0};
	obj.color_type = C_TEXTURE;
	obj.opacity = g_plane_default_opacity;
	obj.reflection = g_plane_default_reflection;
	obj.density = g_plane_default_density;
	return (scene_add_object(state->scene, &obj));
}
