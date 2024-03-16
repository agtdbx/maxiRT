/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_parsing_to_object_file_bonus.c               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auguste <auguste@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 12:22:57 by auguste           #+#    #+#             */
/*   Updated: 2024/03/16 15:54:05 by auguste          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt/parser/dot_obj_file/dot_obj_file_bonus.h"

bool	apply_parsing_to_object_file(
			t_object_file *const objf,
			t_parse_dot_struct *parse_dot_struct)
{
	(void)objf;
	parse_dot_struct_free(parse_dot_struct);
	return (true);
}
