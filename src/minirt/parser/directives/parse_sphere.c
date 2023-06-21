/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_sphere.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouba <aderouba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 16:38:48 by tdubois           #+#    #+#             */
/*   Updated: 2023/06/21 15:57:05 by aderouba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt/parser/parser.h"

#include "libft/libft.h"

#include "minirt/app/scene/scene.h"
#include "minirt/app/app_config.h"

t_error	parse_sphere(
			t_parser_state *state)
{
	t_object	obj;
	t_sphere	*const sphere = &obj.value.as_sphere;

	ft_bzero(&obj, sizeof(t_object));
	if (parse_field(state, &g_position, &sphere->pos) == FAILURE
		|| parse_field(state, &g_diameter, &sphere->diameter) == FAILURE
		|| parse_field(state, &g_color, &obj.color) == FAILURE)
		return (FAILURE);
	// obj.texture = NULL;
	obj.texture = mlx_load_png("imgs/gravel_texture.png");
	// obj.color_type = C_COLOR;
	obj.color_type = C_TEXTURE;
	obj.opacity = g_sphere_default_opacity;
	obj.reflection = g_sphere_default_reflection;
	obj.density = g_sphere_default_density;
	return (scene_add_object(state->scene, &obj));
}
