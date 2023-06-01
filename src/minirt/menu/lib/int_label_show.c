/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   int_label_show.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdubois <tdubois@student.42angouleme.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 09:49:48 by tdubois           #+#    #+#             */
/*   Updated: 2023/06/01 10:03:17 by tdubois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt/menu/menu.h>

#include <stdbool.h>

void	int_label_show(
			t_int_label *label)
{
	label->is_visible = true;
}
