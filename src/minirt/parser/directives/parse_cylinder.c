/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cylinder.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auguste <auguste@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 16:38:48 by tdubois           #+#    #+#             */
/*   Updated: 2023/06/24 17:44:44 by auguste          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt/parser/parser.h"

#include "libft/libft.h"

#include "minirt/app/scene/scene.h"
#include "minirt/app/app_config.h"

t_error	parse_cylinder(
			t_parser_state *state)
{
	t_object	obj;
	t_cylinder	*const cylinder = &obj.value.as_cylinder;

	ft_bzero(&obj, sizeof(t_object));
	if (parse_field(state, &g_position, &cylinder->pos) == FAILURE
		|| parse_field(state, &g_direction, &cylinder->axis) == FAILURE
		|| parse_field(state, &g_diameter, &cylinder->diameter) == FAILURE
		|| parse_field(state, &g_diameter, &cylinder->height) == FAILURE
		|| parse_field(state, &g_color, &obj.color) == FAILURE)
		return (FAILURE);
	obj.type = OBJ_CYLINDER;
	obj.texture = NULL;
	// obj.texture = mlx_load_png("imgs/Bark_texture.png");
	obj.color_type = C_COLOR;
	obj.normal_map = NULL;
	// obj.normal_map = mlx_load_png("imgs/Bark_normal.png");
	obj.opacity = g_cylinder_default_opacity;
	obj.reflection = g_cylinder_default_reflection;
	obj.density = g_cylinder_default_density;
	return (scene_add_object(state->scene, &obj));
}
