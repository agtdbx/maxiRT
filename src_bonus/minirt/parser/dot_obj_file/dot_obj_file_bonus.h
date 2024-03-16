#ifndef DOT_OBJ_FILE_H
# define DOT_OBJ_FILE_H

# include "minirt/app/scene/scene_bonus.h"
# define PARSE_DOT_FILE_SUCCESS -1

typedef	struct s_vertrice
{
	float				x;
	float				y;
	float				z;

	struct s_vertrice	*next;
}	t_vertrice;

typedef	struct s_face
{
	int				p1;
	int				p2;
	int				p3;

	struct s_face	*next;
}	t_face;

typedef	struct s_parse_dot_struct
{
	t_vertrice	*vertrices;
	t_face		*faces;
	int			nb_vertrices;
	int			nb_faces;
}	t_parse_dot_struct;


bool	parse_dot_struct_add_vertrice(
			t_parse_dot_struct *parse_dot_struct,
			float x, float y, float z);
bool	parse_dot_struct_add_face(
			t_parse_dot_struct *parse_dot_struct,
			int p1, int p2, int p3);
void	parse_dot_struct_free(
			t_parse_dot_struct *parse_dot_struct);


int		parse_dot_file(
			int fd,
			t_parse_dot_struct *parse_dot_struct);
bool	apply_parsing_to_object_file(
			t_object_file *const objf,
			t_parse_dot_struct *parse_dot_struct);

#endif
