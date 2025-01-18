/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec2_label_hide.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gugus <gugus@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 19:54:53 by gugus             #+#    #+#             */
/*   Updated: 2025/01/18 19:56:29 by gugus            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt/app/menu/menu.h"

#include <stdbool.h>
#include <stddef.h>

void	vec2_label_hide(
			t_vec2_label *label)
{
	if (label->img_title != NULL)
		label->img_title->enabled = false;
	float_label_hide(&label->label_x);
	float_label_hide(&label->label_y);
}
