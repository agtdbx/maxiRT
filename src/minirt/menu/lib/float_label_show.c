/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   float_label_show.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdubois <tdubois@student.42angouleme.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 17:09:56 by tdubois           #+#    #+#             */
/*   Updated: 2023/05/31 17:20:51 by tdubois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt/menu/menu.h>

#include <stdbool.h>

void	float_label_show(
			t_float_label *label)
{
	label->is_visible = true;
}
