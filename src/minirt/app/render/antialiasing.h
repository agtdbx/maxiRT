/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   antialiasing.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damien <damien@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 20:15:49 by damien            #+#    #+#             */
/*   Updated: 2025/01/18 20:16:33 by damien           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ANTIALIASING_H
# define ANTIALIASING_H

# include "minirt/app/utils/geometry/geometry.h"

typedef struct s_edge
{
	t_vec2	pixel_pos;
	t_vec2	init_pixel_pos;
	t_vec2	pixel_step;
	float	luma;
	float	other_luma;
	bool	horizontal;
}	t_edge;


typedef struct s_luma_neighbour
{
	float middle;
	float up;
	float down;
	float left;
	float right;
	float left_up;
	float right_up;
	float left_down;
	float right_down;
}	t_luma_neighbour;


#endif //ANTIALIASING_H