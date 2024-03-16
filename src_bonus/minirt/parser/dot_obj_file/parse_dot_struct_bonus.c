/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_dot_struct_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auguste <auguste@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 12:34:56 by auguste           #+#    #+#             */
/*   Updated: 2024/03/16 12:46:30 by auguste          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt/parser/dot_obj_file/dot_obj_file_bonus.h"

#include <stdlib.h>

bool	parse_dot_struct_add_vertrice(
			t_parse_dot_struct *parse_dot_struct,
			float x, float y, float z)
{
	t_vertrice	*vertrice;
	t_vertrice	*tmp;

	vertrice = malloc(sizeof(t_vertrice));
	if (vertrice == NULL)
		return (false);
	vertrice->x = x;
	vertrice->y = y;
	vertrice->z = z;
	vertrice->next = NULL;
	tmp = parse_dot_struct->vertrices;
	if (tmp == NULL)
	{
		parse_dot_struct->vertrices = vertrice;
		return (true);
	}
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = vertrice;
	return (true);
}


bool	parse_dot_struct_add_face(
			t_parse_dot_struct *parse_dot_struct,
			int p1, int p2, int p3)
{
	t_face	*face;
	t_face	*tmp;

	face = malloc(sizeof(t_face));
	if (face == NULL)
		return (false);
	face->p1 = p1;
	face->p2 = p2;
	face->p3 = p3;
	face->next = NULL;
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
			t_parse_dot_struct *parse_dot_struct);
