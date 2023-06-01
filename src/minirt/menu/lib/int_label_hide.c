/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   int_label_hide.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdubois <tdubois@student.42angouleme.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 09:50:23 by tdubois           #+#    #+#             */
/*   Updated: 2023/06/01 10:03:42 by tdubois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt/menu/menu.h>

#include <stdbool.h>

void	int_label_hide(
			t_int_label *label)
{
	label->is_visible = false;
	if (label->img != NULL)
		label->img->enabled = false;
}
