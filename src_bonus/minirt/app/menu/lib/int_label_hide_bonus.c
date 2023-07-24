/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   int_label_hide.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdubois <tdubois@student.42angouleme.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 09:50:23 by tdubois           #+#    #+#             */
/*   Updated: 2023/06/23 18:41:56 by tdubois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt/app/menu/menu_bonus.h"

#include <stdbool.h>
#include <stddef.h>

void	int_label_hide(
			t_int_label *label)
{
	if (label->img != NULL)
		label->img->enabled = false;
}
