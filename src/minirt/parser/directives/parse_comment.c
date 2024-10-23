/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_comment.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auguste <auguste@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 16:38:48 by tdubois           #+#    #+#             */
/*   Updated: 2024/03/16 21:20:17 by auguste          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt/parser/parser.h"

#include <stdio.h>
#include <stddef.h>

#include "libft/libft.h"

#include "minirt/app/scene/scene.h"

t_error	parse_comment(
			t_parser_state *state)
{
	while (ft_strtok(NULL, " ") != NULL)
		;
	(void)state;
	return (SUCCESS);
}
