/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   button_hide.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdubois <tdubois@student.42angouleme.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 16:41:53 by tdubois           #+#    #+#             */
/*   Updated: 2023/07/17 09:12:20 by tdubois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt/app/menu/menu_bonus.h"

void	button_hide(
			t_button *button)
{
	if (button->img != NULL && button->img->instances != NULL)
		button->img->instances->enabled = false;
	if (button->img_minus != NULL && button->img_minus->instances != NULL)
		button->img_minus->instances->enabled = false;
	if (button->img_plus != NULL && button->img_plus->instances != NULL)
		button->img_plus->instances->enabled = false;
}
