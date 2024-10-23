#ifndef DOT_OBJ_FILE_H
# define DOT_OBJ_FILE_H

# include "minirt/app/scene/scene.h"
# define PARSE_DOT_FILE_SUCCESS -1

typedef	enum e_face_t
{
	FACE_TRIANGLE,
	FACE_RECTANGLE
}	t_face_t;

typedef	struct s_vertice
{
	float				x;
	float				y;
	float				z;

	struct s_vertice	*next;
}	t_vertice;

typedef	struct s_face
{
	int				p1;
	int				p2;
	int				p3;
	int				p4;
	t_face_t		type;

	struct s_face	*next;
}	t_face;

typedef	struct s_parse_dot_struct
{
	t_vertice	*vertices;
	t_face		*faces;
	int			nb_vertices;
	int			nb_faces;
}	t_parse_dot_struct;


void	parse_dot_struct_add_init(
			t_parse_dot_struct *parse_dot_struct);
bool	parse_dot_struct_add_vertice(
			t_parse_dot_struct *parse_dot_struct,
			float x, float y, float z);
bool	parse_dot_struct_add_face_triangle(
			t_parse_dot_struct *parse_dot_struct,
			int p1, int p2, int p3);
bool	parse_dot_struct_add_face_rectangle(
			t_parse_dot_struct *parse_dot_struct,
			int p1, int p2, int p3, int p4);
void	parse_dot_struct_free(
			t_parse_dot_struct *parse_dot_struct);


int		parse_dot_file(
			int fd,
			t_parse_dot_struct *parse_dot_struct);
bool	apply_parsing_to_object_file(
			t_object_file *const objf,
			t_parse_dot_struct *parse_dot_struct);

#endif
