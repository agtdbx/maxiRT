/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_label_hide.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdubois <tdubois@student.42angouleme.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 17:08:01 by tdubois           #+#    #+#             */
/*   Updated: 2023/05/31 17:37:47 by tdubois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt/menu/menu.h>

#include <stdbool.h>

void	vec3_label_hide(
			t_vec3_label *label)
{
	label->is_visible = false;
	if (label->img_title != NULL)
		label->img_title->enabled = false;
	float_label_hide(&label->label_x);
	float_label_hide(&label->label_y);
	float_label_hide(&label->label_z);
}
