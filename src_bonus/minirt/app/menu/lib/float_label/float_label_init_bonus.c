/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   float_label_init.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdubois <tdubois@student.42angouleme.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 09:13:24 by tdubois           #+#    #+#             */
/*   Updated: 2023/07/03 09:16:47 by tdubois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt/app/menu/menu_bonus.h"

#include <stdint.h>

void	float_label_init(
			t_float_label *label,
			char const *str,
			uint32_t pos[2])
{
	label->prefix = str;
	label->x = pos[0];
	label->y = pos[1];
	label->f = NULL;
	label->img = NULL;
}
