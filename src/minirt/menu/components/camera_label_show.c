/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_label_show.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdubois <tdubois@student.42angouleme.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 16:44:24 by tdubois           #+#    #+#             */
/*   Updated: 2023/05/31 21:37:51 by tdubois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt/menu/menu.h>

void	camera_label_show(
			t_menu *menu)
{
	menu->camera_label_title->enabled = true;
	vec3_label_show(&menu->camera_dir_label);
	vec3_label_show(&menu->camera_pos_label);
}
