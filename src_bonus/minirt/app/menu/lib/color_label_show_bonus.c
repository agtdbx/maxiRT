/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_label_show.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdubois <tdubois@student.42angouleme.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 10:02:11 by tdubois           #+#    #+#             */
/*   Updated: 2023/06/23 18:44:49 by tdubois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt/app/menu/menu_bonus.h"

#include <stdbool.h>
#include <stddef.h>

void	color_label_show(
			t_color_label *label)
{
	if (label->img_title != NULL)
		label->img_title->enabled = true;
	int_label_show(&label->label_r);
	int_label_show(&label->label_g);
	int_label_show(&label->label_b);
}
