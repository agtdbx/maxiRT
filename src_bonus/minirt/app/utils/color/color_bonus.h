/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdubois <tdubois@student.42angouleme.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 01:27:52 by tdubois           #+#    #+#             */
/*   Updated: 2023/06/09 14:46:29 by tdubois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLOR_H
# define COLOR_H

# include <stdint.h>

# include "minirt/app/app_config_bonus.h"

typedef struct s_color
{
	float	r;
	float	g;
	float	b;
}	t_color;

int32_t	color_to_int(
			t_color const *color);

void	color_scale(
			t_color *color,
			float scaling_factor);

#endif//COLOR_H
