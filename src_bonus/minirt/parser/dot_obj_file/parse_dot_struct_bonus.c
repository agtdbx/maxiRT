/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_dot_struct_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auguste <auguste@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 12:34:56 by auguste           #+#    #+#             */
/*   Updated: 2024/03/16 16:57:37 by auguste          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt/parser/dot_obj_file/dot_obj_file_bonus.h"

#include <stdlib.h>
#include <stdio.h>

void	parse_dot_struct_add_init(
			t_parse_dot_struct *parse_dot_struct)
{
	parse_dot_struct->nb_faces = 0;
	parse_dot_struct->nb_vertices = 0;
	parse_dot_struct->faces = NULL;
	parse_dot_struct->vertices = NULL;
}


bool	parse_dot_struct_add_vertice(
			t_parse_dot_struct *parse_dot_struct,
			float x, float y, float z)
{
	t_vertice	*vertice;
	t_vertice	*tmp;

	if (parse_dot_struct == NULL)
		return (false);

	// Create the new vertice
	vertice = malloc(sizeof(t_vertice));
	if (vertice == NULL)
	{
		parse_dot_struct_free(parse_dot_struct);
		return (false);
	}
	vertice->x = x;
	vertice->y = y;
	vertice->z = z;
	vertice->next = NULL;

	// Add the new vertice at the parse_dot_struct
	parse_dot_struct->nb_vertices++;
	tmp = parse_dot_struct->vertices;
	if (tmp == NULL)
	{
		parse_dot_struct->vertices = vertice;
		return (true);
	}
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = vertice;
	return (true);
}


bool	parse_dot_struct_add_face(
			t_parse_dot_struct *parse_dot_struct,
			int p1, int p2, int p3)
{
	t_face	*face;
	t_face	*tmp;

	if (parse_dot_struct == NULL)
		return (false);

	// Create the new face
	face = malloc(sizeof(t_face));
	if (face == NULL)
	{
		parse_dot_struct_free(parse_dot_struct);
		return (false);
	}
	face->p1 = p1;
	face->p2 = p2;
	face->p3 = p3;
	face->next = NULL;

	// Add the new face at the parse_dot_struct
	parse_dot_struct->nb_faces++;
	tmp = parse_dot_struct->faces;
	if (tmp == NULL)
	{
		parse_dot_struct->faces = face;
		return (true);
	}
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = face;
	return (true);
}


void	parse_dot_struct_free(
			t_parse_dot_struct *parse_dot_struct)
{
	t_face	*actual_face;
	t_face	*next_face;
	t_vertice	*actual_vertice;
	t_vertice	*next_vertice;

	if (parse_dot_struct == NULL)
		return ;

	// free vertices
	actual_vertice = parse_dot_struct->vertices;
	while (actual_vertice && actual_vertice->next)
	{
		next_vertice = actual_vertice->next;
		free(actual_vertice);
		actual_vertice = next_vertice;
	}
	if (actual_vertice)
		free(actual_vertice);

	// free faces
	actual_face = parse_dot_struct->faces;
	while (actual_face && actual_face->next)
	{
		next_face = actual_face->next;
		free(actual_face);
		actual_face = next_face;
	}
	if (actual_face)
		free(actual_face);

	parse_dot_struct->faces = NULL;
	parse_dot_struct->vertices = NULL;
}
