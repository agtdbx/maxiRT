/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cone.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouba <aderouba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 16:38:48 by tdubois           #+#    #+#             */
/*   Updated: 2023/06/23 16:20:23 by aderouba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt/parser/parser.h"

#include "libft/libft.h"

#include "minirt/app/scene/scene.h"
#include "minirt/app/app_config.h"

t_error	parse_cone(
			t_parser_state *state)
{
	t_object	obj;
	t_cone	*const cone = &obj.value.as_cone;

	ft_bzero(&obj, sizeof(t_object));
	if (parse_field(state, &g_position, &cone->pos) == FAILURE
		|| parse_field(state, &g_direction, &cone->axis) == FAILURE
		|| parse_field(state, &g_diameter, &cone->diameter) == FAILURE
		|| parse_field(state, &g_diameter, &cone->height) == FAILURE
		|| parse_field(state, &g_color, &obj.color) == FAILURE)
		return (FAILURE);
	obj.type = OBJ_CONE;
	obj.texture = NULL;
	// obj.texture = mlx_load_png("imgs/Bark_texture.png");
	obj.color_type = C_COLOR;
	obj.normal_map = NULL;
	// obj.normal_map = mlx_load_png("imgs/Bark_normal.png");
	obj.opacity = g_cone_default_opacity;
	obj.reflection = g_cone_default_reflection;
	obj.density = g_cone_default_density;
	return (scene_add_object(state->scene, &obj));
}
