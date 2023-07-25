/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_comment_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouba <aderouba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 16:38:48 by tdubois           #+#    #+#             */
/*   Updated: 2023/07/25 14:51:31 by aderouba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt/parser/parser_bonus.h"

#include <stdio.h>
#include <stddef.h>

#include "libft/libft.h"

#include "minirt/app/scene/scene_bonus.h"

t_error	parse_comment(
			t_parser_state *state)
{
	while (ft_strtok(NULL, " ") != NULL)
		;
	(void)state;
	return (SUCCESS);
}
