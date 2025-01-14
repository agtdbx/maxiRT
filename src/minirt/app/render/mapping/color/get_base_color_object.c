/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_base_color_object.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damien <damien@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 12:52:20 by aderouba          #+#    #+#             */
/*   Updated: 2024/12/26 16:39:08 by damien           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt/app/app.h"

static t_color	apply_checkboard(
					float w,
					float h,
					t_vec2 const *pixel_pos);

static t_color	_apply_face_texture(
					mlx_texture_t *textures,
					t_intersect_info const *intersect_info,
					t_vec2 const *pixel_pos);

t_color	get_base_color_object(
			t_object const *intersected_object,
			t_intersect_info const *intersect_info,
			t_vec2 const *pixel_pos)
{
	if (intersected_object->color_type == C_COLOR)
		return (intersected_object->color);
	else if (intersected_object->color_type == C_CHECKBOARD)
		return (apply_checkboard(8.0f, 8.0f, pixel_pos));
	else
	{
		if (intersected_object->type == OBJ_SKYBOX)
			return (_apply_face_texture(intersected_object->value.as_skybox.textures, intersect_info, pixel_pos));
		return (apply_texture(intersected_object->texture, pixel_pos));
	}
}

static t_color	apply_checkboard(float w, float h, t_vec2 const *pixel_pos)
{
	t_color	res;

	res = (t_color){0};
	if (((int)(pixel_pos->x * w) + (int)(pixel_pos->y * h)) % 2)
	{
		res.r = 255;
		res.g = 255;
		res.b = 255;
	}
	return (res);
}

static t_color	_apply_face_texture(
					mlx_texture_t *textures,
					t_intersect_info const *intersect_info,
					t_vec2 const *pixel_pos)
{
	switch(intersect_info->sub_part_id)
	{
		case 0:
			return (apply_texture(&textures[0], pixel_pos));
		case 1:
			return (apply_texture(&textures[1], pixel_pos));
		case 2:
			return (apply_texture(&textures[2], pixel_pos));
		case 3:
			return (apply_texture(&textures[3], pixel_pos));
		case 4:
			return (apply_texture(&textures[4], pixel_pos));
		default:
			break;
	}
	return (apply_texture(&textures[5], pixel_pos));
}
