/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   int_label_init.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdubois <tdubois@student.42angouleme.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 10:14:02 by tdubois           #+#    #+#             */
/*   Updated: 2023/07/03 10:15:09 by tdubois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt/app/menu/menu_bonus.h"

#include <stdint.h>

void	int_label_init(
			t_int_label *label,
			char const *prefix,
			uint32_t const pos[2])
{
	label->prefix = prefix;
	label->x = pos[0];
	label->y = pos[1];
	label->f = NULL;
	label->img = NULL;
}
