/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_skybox.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damien <damien@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 16:36:53 by damien            #+#    #+#             */
/*   Updated: 2024/12/26 23:13:41 by damien           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42/MLX42.h"

#include "minirt/parser/parser.h"
#include "minirt/app/scene/scene.h"
#include "minirt/app/app_config.h"

#include <stdlib.h>

#define X 0
#define Y 1
#define NB_FACES 6
#define SKYBOX_WIDTH 1000000.0f
#define SKYBOX_HEIGHT 1000000.0f
#define SKYBOX_DEPTH 1000000.0f

static t_error	extract_faces_textures(t_object *obj);

t_error	parse_skybox(t_parser_state *state)
{
	t_object	obj;

	if (parse_field(state, &g_png, &obj.texture) == FAILURE)
		return FAILURE;
	obj.type = OBJ_SKYBOX;
	obj.value.as_skybox.cube.pos = (t_vec3){0, 0, 0};
	obj.value.as_skybox.cube.x_axis = (t_vec3){1, 0, 0};
	obj.value.as_skybox.cube.y_axis = (t_vec3){0, 1, 0};
	obj.value.as_skybox.cube.z_axis = (t_vec3){0, 0, 1};
	obj.value.as_skybox.cube.witdh = SKYBOX_WIDTH;
	obj.value.as_skybox.cube.height = SKYBOX_HEIGHT;
	obj.value.as_skybox.cube.depth = SKYBOX_DEPTH;
	obj.color_type = C_TEXTURE;
	obj.opacity = g_cube_default_opacity;
	obj.density = g_cube_default_density;
	obj.reflection = g_cube_default_reflection;
	obj.normal_map = NULL;
	if (extract_faces_textures(&obj) == FAILURE)
		return FAILURE;
	return (scene_add_object(state->scene, &obj));
}

static uint8_t	*extract_face_pixels(int start[2], const int face_height,
	const int face_width, const int face_size, mlx_texture_t *texture)
{
	int	i;
	int	j;
	uint8_t* pixeli;
	uint8_t* pixelx;
	uint8_t	*pixels = malloc(face_size);
	if (pixels == NULL)
		return NULL;

	for (i = start[Y]; i < start[Y] + face_height; i++)
	{
		for (j = start[X]; j < start[X] + face_width; j++)
		{
			pixelx = &texture->pixels[(i * texture->width + j) * texture->bytes_per_pixel];
			pixeli = &pixels[((i - start[Y]) * face_width + (j - start[X])) * texture->bytes_per_pixel];
			ft_memcpy(pixeli, pixelx, texture->bytes_per_pixel);
		}
	}

	return pixels;
}

static t_error	extract_faces_textures(t_object *obj)
{
	uint8_t		*pixels;
	int			i;
	int			face_size;
	int			start[2];
	const int	face_width = obj->texture->width / 4;
	const int	face_height = obj->texture->height / 3;
	struct s_faces_pos {
		int	x;
		int	y;
	} faces[NB_FACES] = {
		{0, 0},
		{0, face_height},
		{face_width, 0},
		{face_width, 2 * face_height},
		{face_width, face_height},
		{3 * face_width, face_height}
	};

	obj->value.as_skybox.textures = malloc(sizeof(mlx_texture_t) * NB_FACES);
	if (obj->value.as_skybox.textures == NULL)
		return FAILURE;
	face_size = sizeof(uint8_t) * obj->texture->bytes_per_pixel * face_width
		* face_height;
	for (i = 0; i < NB_FACES; i++)
	{
		start[X] = faces[i].x;
		start[Y] = faces[i].y;
		pixels = extract_face_pixels(start, face_height, face_width,face_size, obj->texture);
		if (pixels == NULL)
			return FAILURE;
		obj->value.as_skybox.textures[i].pixels = pixels;
		obj->value.as_skybox.textures[i].width = face_width;
		obj->value.as_skybox.textures[i].height = face_height;
		obj->value.as_skybox.textures[i].bytes_per_pixel = obj->texture->bytes_per_pixel;
	}
	return SUCCESS;
}
