/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_label_hide.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdubois <tdubois@student.42angouleme.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 17:39:29 by tdubois           #+#    #+#             */
/*   Updated: 2023/05/31 17:39:49 by tdubois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt/menu/menu.h>

void	camera_label_hide(
			t_menu *menu)
{
	vec3_label_hide(&menu->camera_dir_label);
	vec3_label_hide(&menu->camera_pos_label);
}
