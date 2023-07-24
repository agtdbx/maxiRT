/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_label_hide.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdubois <tdubois@student.42angouleme.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 10:04:28 by tdubois           #+#    #+#             */
/*   Updated: 2023/06/23 18:44:38 by tdubois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt/app/menu/menu_bonus.h"

#include <stdbool.h>
#include <stddef.h>

void	color_label_hide(
			t_color_label *label)
{
	if (label->img_title != NULL)
		label->img_title->enabled = false;
	int_label_hide(&label->label_r);
	int_label_hide(&label->label_g);
	int_label_hide(&label->label_b);
}
