/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_label_show.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdubois <tdubois@student.42angouleme.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 16:47:03 by tdubois           #+#    #+#             */
/*   Updated: 2023/06/23 18:42:11 by tdubois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt/app/menu/menu.h"

#include <stdbool.h>
#include <stddef.h>

void	vec3_label_show(
			t_vec3_label *label)
{
	if (label->img_title != NULL)
		label->img_title->enabled = true;
	float_label_show(&label->label_x);
	float_label_show(&label->label_y);
	float_label_show(&label->label_z);
}
