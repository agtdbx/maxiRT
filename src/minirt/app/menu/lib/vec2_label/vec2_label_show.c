/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec2_label_show.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gugus <gugus@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 19:54:35 by gugus             #+#    #+#             */
/*   Updated: 2025/01/18 19:55:58 by gugus            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt/app/menu/menu.h"

#include <stdbool.h>
#include <stddef.h>

void	vec2_label_show(
			t_vec2_label *label)
{
	if (label->img_title != NULL)
		label->img_title->enabled = true;
	float_label_show(&label->label_x);
	float_label_show(&label->label_y);
}
