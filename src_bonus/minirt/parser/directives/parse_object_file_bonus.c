/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_object_file_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gugus <gugus@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 16:38:48 by tdubois           #+#    #+#             */
/*   Updated: 2024/06/16 16:36:45 by gugus            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt/parser/parser_bonus.h"

#include "libft/libft.h"

#include "minirt/app/scene/scene_bonus.h"
#include "minirt/app/app_config_bonus.h"

t_error	parse_object_file(
			t_parser_state *state)
{
	t_object				obj;
	t_object_file *const	objf = &obj.value.as_object_file;

	ft_bzero(&obj, sizeof(t_object));
	if (parse_field(state, &g_position, &objf->pos) == FAILURE
		|| parse_field(state, &g_direction, &objf->x_axis) == FAILURE
		|| parse_field(state, &g_direction, &objf->y_axis) == FAILURE
		|| parse_field(state, &g_diameter, &objf->size) == FAILURE
		|| parse_field(state, &g_objf, objf) == FAILURE
		|| parse_field(state, &g_color, &obj.color) == FAILURE)
		return (FAILURE);
	if (vec3_dot(&objf->x_axis, &objf->y_axis) != 0.0f)
	{
		return (FAILURE);
	}
	obj.type = OBJ_OBJECT_FILE;
	obj.texture = NULL;
	obj.color_type = C_COLOR;
	obj.normal_map = NULL;
	obj.opacity = g_object_file_default_opacity;
	obj.reflection = g_object_file_default_reflection;
	obj.density = g_object_file_default_density;
	objf->pos.y += 0.001f;
	return (scene_add_object(state->scene, &obj));
}

t_error	parse_object_file_checkerboard(
			t_parser_state *state)
{
	t_object		obj;
	t_object_file *const	objf = &obj.value.as_object_file;

	ft_bzero(&obj, sizeof(t_object));
	if (parse_field(state, &g_position, &objf->pos) == FAILURE
		|| parse_field(state, &g_direction, &objf->x_axis) == FAILURE
		|| parse_field(state, &g_direction, &objf->y_axis) == FAILURE
		|| parse_field(state, &g_diameter, &objf->size) == FAILURE
		|| parse_field(state, &g_objf, objf) == FAILURE)
		return (FAILURE);
	if (vec3_dot(&objf->x_axis, &objf->y_axis) != 0.0f)
	{
		return (FAILURE);
	}
	obj.type = OBJ_OBJECT_FILE;
	obj.texture = NULL;
	obj.color = (t_color){0};
	obj.color_type = C_CHECKBOARD;
	obj.normal_map = NULL;
	obj.opacity = g_object_file_default_opacity;
	obj.reflection = g_object_file_default_reflection;
	obj.density = g_object_file_default_density;
	objf->pos.y += 0.001f;
	return (scene_add_object(state->scene, &obj));
}

t_error	parse_object_file_texture(
			t_parser_state *state)
{
	t_object		obj;
	t_object_file *const	objf = &obj.value.as_object_file;

	ft_bzero(&obj, sizeof(t_object));
	if (parse_field(state, &g_position, &objf->pos) == FAILURE
		|| parse_field(state, &g_direction, &objf->x_axis) == FAILURE
		|| parse_field(state, &g_direction, &objf->y_axis) == FAILURE
		|| parse_field(state, &g_diameter, &objf->size) == FAILURE
		|| parse_field(state, &g_objf, objf) == FAILURE
		|| parse_field(state, &g_png, &obj.texture) == FAILURE)
		return (FAILURE);
	if (vec3_dot(&objf->x_axis, &objf->y_axis) != 0.0f)
	{
		return (FAILURE);
	}
	obj.type = OBJ_OBJECT_FILE;
	obj.color = (t_color){0};
	obj.color_type = C_TEXTURE;
	obj.normal_map = NULL;
	obj.opacity = g_object_file_default_opacity;
	obj.reflection = g_object_file_default_reflection;
	obj.density = g_object_file_default_density;
	objf->pos.y += 0.001f;
	return (scene_add_object(state->scene, &obj));
}

t_error	parse_object_file_texture_and_normal(
			t_parser_state *state)
{
	t_object		obj;
	t_object_file *const	objf = &obj.value.as_object_file;

	ft_bzero(&obj, sizeof(t_object));
	if (parse_field(state, &g_position, &objf->pos) == FAILURE
		|| parse_field(state, &g_direction, &objf->x_axis) == FAILURE
		|| parse_field(state, &g_direction, &objf->y_axis) == FAILURE
		|| parse_field(state, &g_diameter, &objf->size) == FAILURE
		|| parse_field(state, &g_objf, objf) == FAILURE
		|| parse_field(state, &g_png, &obj.texture) == FAILURE)
		return (FAILURE);
	if (parse_field(state, &g_png, &obj.normal_map) == FAILURE)
	{
		mlx_delete_texture(obj.texture);
		return (FAILURE);
	}
	if (vec3_dot(&objf->x_axis, &objf->y_axis) != 0.0f)
	{
		mlx_delete_texture(obj.texture);
		mlx_delete_texture(obj.normal_map);
		return (FAILURE);
	}
	obj.type = OBJ_OBJECT_FILE;
	obj.color = (t_color){0};
	obj.color_type = C_TEXTURE;
	obj.opacity = g_object_file_default_opacity;
	obj.reflection = g_object_file_default_reflection;
	obj.density = g_object_file_default_density;
	objf->pos.y += 0.001f;
	return (scene_add_object(state->scene, &obj));
}
