/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_skybox.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damien <damien@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 16:36:53 by damien            #+#    #+#             */
/*   Updated: 2024/12/26 16:48:17 by damien           ###   ########.fr       */
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

static t_error	extract_faces_textures(t_object *obj);

t_error parse_skybox(t_parser_state *state)
{
	t_object	obj;

	if (parse_field(state, &g_png, &obj.texture) == FAILURE)
		return FAILURE;
	obj.type = OBJ_SKYBOX;
	obj.value.as_skybox.cube.pos = (t_vec3){0, 0, 0};
	obj.value.as_skybox.cube.x_axis = (t_vec3){1, 0, 0};
	obj.value.as_skybox.cube.y_axis = (t_vec3){0, 1, 0};
	obj.value.as_skybox.cube.z_axis = (t_vec3){0, 0, 1};
	obj.value.as_skybox.cube.witdh = 100000.0f;
	obj.value.as_skybox.cube.height = 100000.0f;
	obj.value.as_skybox.cube.depth = 100000.0f;
	obj.color_type = C_TEXTURE;
	obj.color  = (t_color){255, 0, 0};
	obj.opacity = g_cube_default_opacity;
	obj.density = g_cube_default_density;
	obj.reflection = g_cube_default_reflection;
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
	int			face_size;
	int			start[2];
	const int	face_width = obj->texture->width / 4;
	const int	face_height = obj->texture->height / 3;

	obj->value.as_skybox.textures = malloc(sizeof(mlx_texture_t) * NB_FACES);
	if (obj->value.as_skybox.textures == NULL)
		return FAILURE;

	//TOP FACE
	start[X] = face_width;
	start[Y] = 0;

	face_size = sizeof(uint8_t) * obj->texture->bytes_per_pixel * face_width
		* face_height;

	pixels = extract_face_pixels(start, face_height, face_width,face_size, obj->texture);

	obj->value.as_skybox.textures[0].pixels = pixels;
	obj->value.as_skybox.textures[0].width = face_width;
	obj->value.as_skybox.textures[0].height = face_height;
	obj->value.as_skybox.textures[0].bytes_per_pixel = obj->texture->bytes_per_pixel;

	//BOTTOM FACE
	start[X] = face_width;
	start[Y] = face_height * 2;

	pixels = extract_face_pixels(start, face_height, face_width,
		face_size, obj->texture);

	obj->value.as_skybox.textures[1].pixels = pixels;
	obj->value.as_skybox.textures[1].width = face_width;
	obj->value.as_skybox.textures[1].height = face_height;
	obj->value.as_skybox.textures[1].bytes_per_pixel = obj->texture->bytes_per_pixel;


	//LEFT FACE
	start[X] = 0;
	start[Y] = face_height;

	pixels = extract_face_pixels(start, face_height, face_width,
		face_size, obj->texture);

	obj->value.as_skybox.textures[2].pixels = pixels;
	obj->value.as_skybox.textures[2].width = face_width;
	obj->value.as_skybox.textures[2].height = face_height;
	obj->value.as_skybox.textures[2].bytes_per_pixel = obj->texture->bytes_per_pixel;

	//RIGHT FACE
	start[X] = face_width * 2;
	start[Y] = face_height;

	pixels = extract_face_pixels(start, face_height, face_width,
		face_size, obj->texture);

	obj->value.as_skybox.textures[3].pixels = pixels;
	obj->value.as_skybox.textures[3].width = face_width;
	obj->value.as_skybox.textures[3].height = face_height;
	obj->value.as_skybox.textures[3].bytes_per_pixel = obj->texture->bytes_per_pixel;

	//FRONT FACE
	start[X] = face_width;
	start[Y] = face_height;

	pixels = extract_face_pixels(start, face_height, face_width,
		face_size, obj->texture);
	obj->value.as_skybox.textures[4].pixels = pixels;
	obj->value.as_skybox.textures[4].width = face_width;
	obj->value.as_skybox.textures[4].height = face_height;
	obj->value.as_skybox.textures[4].bytes_per_pixel = obj->texture->bytes_per_pixel;

	//BACK FACE
	start[X] = face_width * 3;
	start[Y] = face_height;

	pixels = extract_face_pixels(start, face_height, face_width,
		face_size, obj->texture);

	obj->value.as_skybox.textures[5].pixels = pixels;
	obj->value.as_skybox.textures[5].width = face_width;
	obj->value.as_skybox.textures[5].height = face_height;
	obj->value.as_skybox.textures[5].bytes_per_pixel = obj->texture->bytes_per_pixel;

	return SUCCESS;
}
