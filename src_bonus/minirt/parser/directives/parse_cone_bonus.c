/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cone.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouba <aderouba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 16:38:48 by tdubois           #+#    #+#             */
/*   Updated: 2023/07/05 17:11:34 by aderouba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt/parser/parser_bonus.h"

#include "libft/libft.h"

#include "minirt/app/scene/scene_bonus.h"
#include "minirt/app/app_config_bonus.h"

t_error	parse_cone(
			t_parser_state *state)
{
	t_object		obj;
	t_cone *const	cone = &obj.value.as_cone;

	ft_bzero(&obj, sizeof(t_object));
	if (parse_field(state, &g_position, &cone->pos) == FAILURE
		|| parse_field(state, &g_direction, &cone->axis) == FAILURE
		|| parse_field(state, &g_diameter, &cone->diameter) == FAILURE
		|| parse_field(state, &g_diameter, &cone->height) == FAILURE
		|| parse_field(state, &g_color, &obj.color) == FAILURE)
		return (FAILURE);
	obj.type = OBJ_CONE;
	obj.texture = NULL;
	obj.color_type = C_COLOR;
	obj.normal_map = NULL;
	obj.opacity = g_cone_default_opacity;
	obj.reflection = g_cone_default_reflection;
	obj.density = g_cone_default_density;
	return (scene_add_object(state->scene, &obj));
}

t_error	parse_cone_checkerboard(
			t_parser_state *state)
{
	t_object		obj;
	t_cone *const	cone = &obj.value.as_cone;

	ft_bzero(&obj, sizeof(t_object));
	if (parse_field(state, &g_position, &cone->pos) == FAILURE
		|| parse_field(state, &g_direction, &cone->axis) == FAILURE
		|| parse_field(state, &g_diameter, &cone->diameter) == FAILURE
		|| parse_field(state, &g_diameter, &cone->height) == FAILURE)
		return (FAILURE);
	obj.type = OBJ_CONE;
	obj.texture = NULL;
	obj.color = (t_color){0};
	obj.color_type = C_CHECKBOARD;
	obj.normal_map = NULL;
	obj.opacity = g_cone_default_opacity;
	obj.reflection = g_cone_default_reflection;
	obj.density = g_cone_default_density;
	return (scene_add_object(state->scene, &obj));
}

t_error	parse_cone_texture(
			t_parser_state *state)
{
	t_object		obj;
	t_cone *const	cone = &obj.value.as_cone;

	ft_bzero(&obj, sizeof(t_object));
	if (parse_field(state, &g_position, &cone->pos) == FAILURE
		|| parse_field(state, &g_direction, &cone->axis) == FAILURE
		|| parse_field(state, &g_diameter, &cone->diameter) == FAILURE
		|| parse_field(state, &g_diameter, &cone->height) == FAILURE
		|| parse_field(state, &g_png, &obj.texture) == FAILURE)
		return (FAILURE);
	obj.type = OBJ_CONE;
	obj.color = (t_color){0};
	obj.color_type = C_TEXTURE;
	obj.normal_map = NULL;
	obj.opacity = g_cone_default_opacity;
	obj.reflection = g_cone_default_reflection;
	obj.density = g_cone_default_density;
	return (scene_add_object(state->scene, &obj));
}

t_error	parse_cone_texture_and_normal(
			t_parser_state *state)
{
	t_object		obj;
	t_cone *const	cone = &obj.value.as_cone;

	ft_bzero(&obj, sizeof(t_object));
	if (parse_field(state, &g_position, &cone->pos) == FAILURE
		|| parse_field(state, &g_direction, &cone->axis) == FAILURE
		|| parse_field(state, &g_diameter, &cone->diameter) == FAILURE
		|| parse_field(state, &g_diameter, &cone->height) == FAILURE
		|| parse_field(state, &g_png, &obj.texture) == FAILURE)
		return (FAILURE);
	if (parse_field(state, &g_png, &obj.normal_map) == FAILURE)
	{
		mlx_delete_texture(obj.texture);
		return (FAILURE);
	}
	obj.type = OBJ_CONE;
	obj.color = (t_color){0};
	obj.color_type = C_TEXTURE;
	obj.opacity = g_cone_default_opacity;
	obj.reflection = g_cone_default_reflection;
	obj.density = g_cone_default_density;
	return (scene_add_object(state->scene, &obj));
}
