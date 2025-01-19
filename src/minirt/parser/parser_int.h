/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_int.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auguste <auguste@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 10:54:46 by tdubois           #+#    #+#             */
/*   Updated: 2024/03/17 13:01:43 by auguste          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_INT_H
# define PARSER_INT_H

# include <stddef.h>

# include "libft/libft.h"

# include "minirt/app/scene/scene.h"

typedef struct s_directive	t_directive;
typedef struct s_field		t_field;

//**** PARSER STATE **********************************************************//

typedef struct s_parser_state
{
	char const			*filename;
	char const			*line;
	size_t				line_number;

	char const			*line_cpy;
	t_directive const	*directive;

	t_field const		*field;
	char				*tok;
	char				*tok_start;

	t_scene				*scene;
}	t_parser_state;

t_error	parse_file(
			char const *path_to_file,
			t_scene *scene);

t_error	parse_directive(
			t_parser_state *state);

//**** PARSER FIELDS *********************************************************//

typedef t_error				(*t_field_cb)(t_parser_state *state, void *data);

struct s_field
{
	char const		*identifier;
	char const		*usage;

	t_field_cb		callback;
};

t_error	parse_field(
			t_parser_state *state,
			t_field const *field,
			void *data);

t_error	parse_vec3(
			t_parser_state *state,
			void *data);

t_error	parse_direction(
			t_parser_state *state,
			void *data);

t_error	parse_color(
			t_parser_state *state,
			void *data);

t_error	parse_float(
			t_parser_state *state,
			void *data);

t_error	parse_brightness(
			t_parser_state *state,
			void *data);

t_error	parse_fov(
			t_parser_state *state,
			void *data);

t_error	parse_diameter(
			t_parser_state *state,
			void *data);

t_error	parse_png(
			t_parser_state *state,
			void *data);

t_error	parse_dot_obj_file(
			t_parser_state *state,
			void *data);

//**** PARSER DIRECTIVES *****************************************************//

typedef t_error				(*t_directive_cb)(t_parser_state *state);

struct s_directive
{
	char const		*identifier;
	char const		*usage;

	t_directive_cb	callback;
};

t_error	parse_lines(
			int fd,
			char const *filename,
			t_scene *scene);

t_error	parse_camera(
			t_parser_state *state);

t_error	parse_ambient_light(
			t_parser_state *state);

t_error	parse_spotlight(
			t_parser_state *state);
t_error	parse_parallel_spotlight(
			t_parser_state *state);

t_error	parse_sphere(
			t_parser_state *state);
t_error	parse_sphere_checkerboard(
			t_parser_state *state);
t_error	parse_sphere_sinusoide(
			t_parser_state *state);
t_error	parse_sphere_perlin_noise(
			t_parser_state *state);
t_error	parse_sphere_texture(
			t_parser_state *state);
t_error	parse_sphere_texture_and_normal(
			t_parser_state *state);

t_error	parse_plane(
			t_parser_state *state);
t_error	parse_plane_checkerboard(
			t_parser_state *state);
t_error	parse_plane_sinusoide(
			t_parser_state *state);
t_error	parse_plane_perlin_noise(
			t_parser_state *state);
t_error	parse_plane_texture(
			t_parser_state *state);
t_error	parse_plane_texture_and_normal(
			t_parser_state *state);

t_error	parse_cylinder(
			t_parser_state *state);
t_error	parse_cylinder_checkerboard(
			t_parser_state *state);
t_error	parse_cylinder_sinusoide(
			t_parser_state *state);
t_error	parse_cylinder_perlin_noise(
			t_parser_state *state);
t_error	parse_cylinder_texture(
			t_parser_state *state);
t_error	parse_cylinder_texture_and_normal(
			t_parser_state *state);

t_error	parse_cone(
			t_parser_state *state);
t_error	parse_cone_checkerboard(
			t_parser_state *state);
t_error	parse_cone_sinusoide(
			t_parser_state *state);
t_error	parse_cone_perlin_noise(
			t_parser_state *state);
t_error	parse_cone_texture(
			t_parser_state *state);
t_error	parse_cone_texture_and_normal(
			t_parser_state *state);

t_error	parse_cube(
			t_parser_state *state);
t_error	parse_cube_checkerboard(
			t_parser_state *state);
t_error	parse_cube_sinusoide(
			t_parser_state *state);
t_error	parse_cube_perlin_noise(
			t_parser_state *state);
t_error	parse_cube_texture(
			t_parser_state *state);
t_error	parse_cube_texture_and_normal(
			t_parser_state *state);

t_error	parse_skybox(
			t_parser_state *state);

t_error	parse_triangle(
			t_parser_state *state);
t_error	parse_triangle_checkerboard(
			t_parser_state *state);
t_error	parse_triangle_sinusoide(
			t_parser_state *state);
t_error	parse_triangle_perlin_noise(
			t_parser_state *state);
t_error	parse_triangle_texture(
			t_parser_state *state);
t_error	parse_triangle_texture_and_normal(
			t_parser_state *state);

t_error	parse_object_file(
			t_parser_state *state);
t_error	parse_object_file_checkerboard(
			t_parser_state *state);
t_error	parse_object_file_sinusoide(
			t_parser_state *state);
t_error	parse_object_file_perlin_noise(
			t_parser_state *state);
t_error	parse_object_file_texture(
			t_parser_state *state);
t_error	parse_object_file_texture_and_normal(
			t_parser_state *state);

t_error	parse_paraboloid(
			t_parser_state *state);
t_error	parse_paraboloid_checkerboard(
			t_parser_state *state);
t_error	parse_paraboloid_texture(
			t_parser_state *state);
t_error	parse_paraboloid_texture_and_normal(
			t_parser_state *state);
t_error	parse_paraboloid_perlin_noise(
			t_parser_state *state);
t_error	parse_paraboloid_sinusoide(
			t_parser_state *state);

t_error	parse_cartoon_effect(
			t_parser_state *state);

t_error	parse_comment(
			t_parser_state *state);

//**** PARSER ERROR LOGGING **************************************************//

void	put_directive_error(
			t_parser_state *state,
			char const *token,
			char const *error);

void	put_unknown_directive_error(
			t_parser_state const *state,
			char const *token);

void	put_field_error(
			t_parser_state *state,
			char const *token,
			char const *error);

#endif//PARSER_INT_H
