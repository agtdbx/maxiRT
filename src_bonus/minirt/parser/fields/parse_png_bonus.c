/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_png.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouba <aderouba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 13:18:51 by tdubois           #+#    #+#             */
/*   Updated: 2023/07/05 16:40:42 by aderouba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt/parser/parser_bonus.h"

#include "libft/libft.h"

//############################################################################//
//#### DECLARATIONS ##########################################################//

t_error	parse_png(
			t_parser_state *state,
			void *data);

//############################################################################//
//#### DEFINITIONS ###########################################################//
t_error	parse_png(
			t_parser_state *state,
			void *data)
{
	mlx_texture_t **const	texture = data;

	*texture = mlx_load_png(state->tok);
	if (*texture == NULL)
	{
		put_field_error(state, state->tok, "Invalid file");
		return (FAILURE);
	}
	return (SUCCESS);
}
