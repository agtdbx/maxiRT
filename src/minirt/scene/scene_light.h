/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_light.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdubois <tdubois@student.42angouleme.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 01:21:43 by tdubois           #+#    #+#             */
/*   Updated: 2023/04/14 01:33:59 by tdubois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENE_LIGHT_H
# define SCENE_LIGHT_H

//> SCENE'S LIGHT OBJECT MODEL
//>
//> modelize spotlights as well as ambient lightning
//> 'pos' field is let unused in the context of ambient lightning

# include <minirt/utils/color.h>
# include <minirt/utils/geometry.h>

typedef struct s_light
{
	t_vec3			pos;
	t_color			color;
	float			brightness;

	struct s_light	*next;
}	t_light;

#endif//SCENE_LIGHT_H
