/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_label_toggle.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdubois <tdubois@student.42angouleme.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 16:44:24 by tdubois           #+#    #+#             */
/*   Updated: 2023/05/31 17:38:51 by tdubois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt/menu/menu.h>

void	camera_label_show(
			t_menu *menu)
{
	vec3_label_show(&menu->camera_dir_label);
	vec3_label_show(&menu->camera_pos_label);
}
