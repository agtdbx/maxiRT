/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_label_show.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdubois <tdubois@student.42angouleme.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 16:47:03 by tdubois           #+#    #+#             */
/*   Updated: 2023/05/31 17:36:23 by tdubois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt/menu/menu.h>

#include <stdbool.h>

void	vec3_label_show(
			t_vec3_label *label)
{
	label->is_visible = true;
	if (label->img_title != NULL)
		label->img_title->enabled = true;
	float_label_show(&label->label_x);
	float_label_show(&label->label_y);
	float_label_show(&label->label_z);
}
