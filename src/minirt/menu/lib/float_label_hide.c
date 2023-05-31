/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   float_label_hide.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdubois <tdubois@student.42angouleme.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 17:22:18 by tdubois           #+#    #+#             */
/*   Updated: 2023/05/31 17:30:09 by tdubois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt/menu/menu.h>

#include <stdbool.h>

void	float_label_hide(
			t_float_label *label)
{
	label->is_visible = false;
	if (label->img != NULL)
		label->img->enabled = false;
}
