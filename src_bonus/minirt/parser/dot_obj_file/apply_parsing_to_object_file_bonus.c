/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_parsing_to_object_file_bonus.c               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auguste <auguste@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 12:22:57 by auguste           #+#    #+#             */
/*   Updated: 2024/03/16 17:38:16 by auguste          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt/parser/dot_obj_file/dot_obj_file_bonus.h"

#include <stdlib.h>

static void	fill_vertices(
			t_object_file *const objf,
			t_parse_dot_struct *parse_dot_struct);
static void	fill_faces(
			t_object_file *const objf,
			t_parse_dot_struct *parse_dot_struct);

bool	apply_parsing_to_object_file(
			t_object_file *const objf,
			t_parse_dot_struct *parse_dot_struct)
{
	if (parse_dot_struct->nb_vertices == 0 ||
		parse_dot_struct->nb_faces == 0)
	{
		parse_dot_struct_free(parse_dot_struct);
		return (false);
	}
	objf->vertices = malloc(sizeof(t_vec3) * parse_dot_struct->nb_vertices);
	if (objf->vertices == NULL)
	{
		parse_dot_struct_free(parse_dot_struct);
		return (false);
	}
	objf->triangles = malloc(sizeof(t_objf_tri) * parse_dot_struct->nb_faces);
	if (objf->triangles == NULL)
	{
		free(objf->vertices);
		parse_dot_struct_free(parse_dot_struct);
		return (false);
	}
	fill_vertices(objf, parse_dot_struct);
	fill_faces(objf, parse_dot_struct);
	parse_dot_struct_free(parse_dot_struct);
	return (true);
}


static void	fill_vertices(
			t_object_file *const objf,
			t_parse_dot_struct *parse_dot_struct)
{
	t_vertice	*actual;
	int			i;

	i = 0;
	actual = parse_dot_struct->vertices;
	while (actual != NULL)
	{
		objf->vertices[i].x = actual->x;
		objf->vertices[i].y = actual->y;
		objf->vertices[i].z = actual->z;
		actual = actual->next;
		i++;
	}
}


static void	fill_faces(
			t_object_file *const objf,
			t_parse_dot_struct *parse_dot_struct)
{
	t_face	*actual;
	int			i;

	i = 0;
	actual = parse_dot_struct->faces;
	while (actual != NULL)
	{
		objf->triangles[i].vertice_1 = actual->p1;
		objf->triangles[i].vertice_2 = actual->p2;
		objf->triangles[i].vertice_3 = actual->p3;
		actual = actual->next;
		i++;
	}
}
