/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cartoon_effect.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gugus <gugus@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 01:45:54 by gugus             #+#    #+#             */
/*   Updated: 2025/01/18 01:53:46 by gugus            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt/parser/parser.h"

#include "libft/libft.h"

#include "minirt/app/scene/scene.h"
#include "minirt/app/app_config.h"

t_error	parse_cartoon_effect(
			t_parser_state *state)
{
	static bool	unique = false;

	if (unique)
		return (FAILURE);
	state->scene->cartoon_effect = true;
	return (SUCCESS);
}
