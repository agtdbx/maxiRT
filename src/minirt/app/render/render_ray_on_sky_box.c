/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_loop_without_param_obj.c           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auguste <auguste@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 19:47:22 by aderouba          #+#    #+#             */
/*   Updated: 2024/04/21 16:29:01 by auguste          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt/app/app.h"

static t_color	_apply_face_texture(
					mlx_texture_t *textures,
					t_intersect_info const *intersect_info,
					t_vec2 const *pixel_pos);

/**
 * Do a loop of intersection with all object without the parameter's one
 * @param[in] object
 * @param[in] scene
 * @param[in] ray
 * @returns The color of the pixel at the ray intersection
 */
t_color	render_ray_on_sky_box(
			t_scene const *scene,
			t_ray const *ray)
{
	t_pixel_info	pixel_info;
	t_color			color;

	t_intersect_info	intersect_info;
	if (!test_intersection_with_cube_from_inside(
			ray, &scene->skybox->value.as_skybox.cube, &intersect_info))
		return ((t_color){0});
	compute_normal_ray(scene->skybox, ray, &intersect_info, &pixel_info.normal);
	pixel_info.pos = get_object_pixel_pos(
						scene->skybox, ray, &pixel_info.normal, &intersect_info);

	color = _apply_face_texture(scene->skybox->value.as_skybox.textures,
								&intersect_info, &pixel_info.pos);
	return (color);
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
