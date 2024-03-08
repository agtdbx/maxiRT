/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_triangle_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auguste <auguste@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 16:38:48 by tdubois           #+#    #+#             */
/*   Updated: 2024/03/08 14:47:47 by auguste          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt/parser/parser_bonus.h"

#include "libft/libft.h"

#include "minirt/app/scene/scene_bonus.h"
#include "minirt/app/app_config_bonus.h"

t_error	parse_triangle(
			t_parser_state *state)
{
	t_object		obj;
	t_triangle *const	triangle = &obj.value.as_triangle;

	ft_bzero(&obj, sizeof(t_object));
	if (parse_field(state, &g_position, &triangle->point1) == FAILURE
		|| parse_field(state, &g_position, &triangle->point2) == FAILURE
		|| parse_field(state, &g_position, &triangle->point3) == FAILURE
		|| parse_field(state, &g_color, &obj.color) == FAILURE)
		return (FAILURE);
	obj.type = OBJ_TRIANGLE;
	obj.texture = NULL;
	obj.color_type = C_COLOR;
	obj.normal_map = NULL;
	obj.opacity = g_triangle_default_opacity;
	obj.reflection = g_triangle_default_reflection;
	obj.density = g_triangle_default_density;
	return (scene_add_object(state->scene, &obj));
}

//t_error	parse_triangle_checkerboard(
//			t_parser_state *state)
//{
//	t_object		obj;
//	t_triangle *const	triangle = &obj.value.as_triangle;

//	ft_bzero(&obj, sizeof(t_object));
//	if (parse_field(state, &g_position, &triangle->pos) == FAILURE
//		|| parse_field(state, &g_direction, &triangle->normal) == FAILURE)
//		return (FAILURE);
//	obj.type = OBJ_triangle;
//	obj.texture = NULL;
//	obj.color = (t_color){0};
//	obj.color_type = C_CHECKBOARD;
//	obj.normal_map = NULL;
//	obj.opacity = g_triangle_default_opacity;
//	obj.reflection = g_triangle_default_reflection;
//	obj.density = g_triangle_default_density;
//	return (scene_add_object(state->scene, &obj));
//}

//t_error	parse_triangle_texture(
//			t_parser_state *state)
//{
//	t_object		obj;
//	t_triangle *const	triangle = &obj.value.as_triangle;

//	ft_bzero(&obj, sizeof(t_object));
//	if (parse_field(state, &g_position, &triangle->pos) == FAILURE
//		|| parse_field(state, &g_direction, &triangle->normal) == FAILURE
//		|| parse_field(state, &g_png, &obj.texture) == FAILURE)
//		return (FAILURE);
//	obj.type = OBJ_triangle;
//	obj.color = (t_color){0};
//	obj.color_type = C_TEXTURE;
//	obj.normal_map = NULL;
//	obj.opacity = g_triangle_default_opacity;
//	obj.reflection = g_triangle_default_reflection;
//	obj.density = g_triangle_default_density;
//	return (scene_add_object(state->scene, &obj));
//}

//t_error	parse_triangle_texture_and_normal(
//			t_parser_state *state)
//{
//	t_object		obj;
//	t_triangle *const	triangle = &obj.value.as_triangle;

//	ft_bzero(&obj, sizeof(t_object));
//	if (parse_field(state, &g_position, &triangle->pos) == FAILURE
//		|| parse_field(state, &g_direction, &triangle->normal) == FAILURE
//		|| parse_field(state, &g_png, &obj.texture) == FAILURE)
//		return (FAILURE);
//	if (parse_field(state, &g_png, &obj.normal_map) == FAILURE)
//	{
//		mlx_delete_texture(obj.texture);
//		return (FAILURE);
//	}
//	obj.type = OBJ_triangle;
//	obj.color = (t_color){0};
//	obj.color_type = C_TEXTURE;
//	obj.opacity = g_triangle_default_opacity;
//	obj.reflection = g_triangle_default_reflection;
//	obj.density = g_triangle_default_density;
//	return (scene_add_object(state->scene, &obj));
//}
