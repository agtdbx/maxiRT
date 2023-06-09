/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_label_hide.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdubois <tdubois@student.42angouleme.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 17:39:29 by tdubois           #+#    #+#             */
/*   Updated: 2023/06/09 14:30:20 by tdubois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt/app/menu/menu.h"

#include <stdbool.h>

#include "minirt/app/utils/geometry/geometry.h"

void	camera_label_hide(
			t_menu *menu)
{
	menu->camera_label_title->enabled = false;
	vec3_label_hide(&menu->camera_dir_label);
	vec3_label_hide(&menu->camera_pos_label);
}
