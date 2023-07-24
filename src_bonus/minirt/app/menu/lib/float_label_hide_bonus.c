/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   float_label_hide.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdubois <tdubois@student.42angouleme.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 17:22:18 by tdubois           #+#    #+#             */
/*   Updated: 2023/06/23 18:45:22 by tdubois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt/app/menu/menu_bonus.h"

#include <stdbool.h>
#include <stddef.h>

void	float_label_hide(
			t_float_label *label)
{
	if (label->img != NULL)
		label->img->enabled = false;
}
