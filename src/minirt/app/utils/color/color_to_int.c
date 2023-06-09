/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_to_int.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdubois <tdubois@student.42angouleme.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 00:53:31 by tdubois           #+#    #+#             */
/*   Updated: 2023/06/09 14:48:36 by tdubois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt/app/utils/color/color.h"

#include <stdint.h>

#include "libft/libft.h"

static	int32_t	_bound(
					float f);

int32_t	color_to_int(
			t_color const *color)
{
	return (255
		| (_bound(color->r) << 24)
		| (_bound(color->g) << 16)
		| (_bound(color->b) << 8));
}

static	int32_t	_bound(
					float f)
{
	if (f < 0.0f)
		return (0);
	if (255.0f < f)
		return (255);
	return (f);
}
