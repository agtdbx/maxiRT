/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   button_show.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdubois <tdubois@student.42angouleme.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 16:40:06 by tdubois           #+#    #+#             */
/*   Updated: 2023/07/17 09:11:16 by tdubois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt/app/menu/menu_bonus.h"

void	button_show(
			t_button *button)
{
	if (button->img != NULL && button->img->instances != NULL)
		button->img->instances->enabled = true;
	if (button->img_minus != NULL && button->img_minus->instances != NULL)
		button->img_minus->instances->enabled = true;
	if (button->img_plus != NULL && button->img_plus->instances != NULL)
		button->img_plus->instances->enabled = true;
}
