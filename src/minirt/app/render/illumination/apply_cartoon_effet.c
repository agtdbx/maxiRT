/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_cartoon_effet.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gugus <gugus@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 18:29:57 by gugus             #+#    #+#             */
/*   Updated: 2025/01/18 18:32:49 by gugus            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt/app/app.h"

#include <minirt/app/scene/scene.h>

void	apply_cartoon_effet(
				t_color *ill,
				float idiffuse)
{
	if (idiffuse > 0.98f)
	{
		ill->r = 0.8f;
		ill->g = 0.8f;
		ill->b = 0.8f;
	}
	else if (idiffuse > 0.5f)
	{
		ill->r = 0.4f;
		ill->g = 0.4f;
		ill->b = 0.8f;
	}
	else if (idiffuse > 0.25f)
	{
		ill->r = 0.2f;
		ill->g = 0.2f;
		ill->b = 0.4f;
	}
	else
	{
		ill->r = 0.1f;
		ill->g = 0.1f;
		ill->b = 0.1f;
	}
}
