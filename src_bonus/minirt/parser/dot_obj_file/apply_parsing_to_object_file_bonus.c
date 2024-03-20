/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_parsing_to_object_file_bonus.c               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auguste <auguste@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 12:22:57 by auguste           #+#    #+#             */
/*   Updated: 2024/03/20 18:37:44 by auguste          ###   ########.fr       */
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
	objf->vertices = NULL;
	objf->real_vertices = NULL;
	objf->polygons = NULL;
	objf->binary_partition = NULL;
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
	objf->real_vertices = malloc(sizeof(t_vec3) * parse_dot_struct->nb_vertices);
	if (objf->real_vertices == NULL)
	{
		free(objf->vertices);
		parse_dot_struct_free(parse_dot_struct);
		return (false);
	}
	objf->polygons = malloc(sizeof(t_object_polygon) * parse_dot_struct->nb_faces);
	if (objf->polygons == NULL)
	{
		free(objf->vertices);
		free(objf->real_vertices);
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
		objf->real_vertices[i].x = actual->x;
		objf->real_vertices[i].y = actual->y;
		objf->real_vertices[i].z = actual->z;
		actual = actual->next;
		i++;
	}
	objf->nb_vertices = parse_dot_struct->nb_vertices;
}


static void	fill_faces(
			t_object_file *const objf,
			t_parse_dot_struct *parse_dot_struct)
{
	t_object_triangle	*objf_triangle;
	t_object_rectangle	*objf_rectangle;
	t_face				*actual;
	int					i;

	i = 0;
	actual = parse_dot_struct->faces;
	while (actual != NULL)
	{
		if (actual->type == FACE_TRIANGLE)
		{
			objf->polygons[i].type = OBJF_TRIANGLE;
			objf_triangle = &objf->polygons[i].value.as_objf_triangle;
			objf_triangle->vertice_1 = actual->p1;
			objf_triangle->vertice_2 = actual->p2;
			objf_triangle->vertice_3 = actual->p3;
		}
		else if (actual->type == FACE_RECTANGLE)
		{
			objf->polygons[i].type = OBJF_RECTANGLE;
			objf_rectangle = &objf->polygons[i].value.as_objf_rectangle;
			objf_rectangle->vertice_1 = actual->p1;
			objf_rectangle->vertice_2 = actual->p2;
			objf_rectangle->vertice_3 = actual->p3;
			objf_rectangle->vertice_4 = actual->p4;
		}
		actual = actual->next;
		i++;
	}
	objf->nb_polygons = parse_dot_struct->nb_faces;
}
