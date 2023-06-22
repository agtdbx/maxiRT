/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_plane.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouba <aderouba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 16:38:48 by tdubois           #+#    #+#             */
/*   Updated: 2023/06/22 12:38:36 by aderouba         ###   ########.fr       */
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
	// obj.texture = mlx_load_png("imgs/Stylized_Stone_texture.png");
	obj.color_type = C_COLOR;
	obj.normal_map = NULL;
	// obj.normal_map = mlx_load_png("imgs/gravel_normal.png");
	// obj.normal_map = mlx_load_png("imgs/Stylized_Stone_normal.png");
	obj.opacity = g_plane_default_opacity;
	obj.reflection = g_plane_default_reflection;
	obj.density = g_plane_default_density;
	return (scene_add_object(state->scene, &obj));
}
