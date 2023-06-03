/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_to_int.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdubois <tdubois@student.42angouleme.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 00:53:31 by tdubois           #+#    #+#             */
/*   Updated: 2023/06/03 02:30:55 by tdubois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt/utils/color.h>

#include <libft/libft.h>
#include <stdint.h>

int32_t	color_to_int(
			t_color const *color)
{
	return (255
		| ft_max(0, ft_min(255, (int)color->r) << 24)
		| ft_max(0, ft_min(255, (int)color->g) << 16)
		| ft_max(0, ft_min(255, (int)color->b) << 8));
}
