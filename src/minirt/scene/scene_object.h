/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_object.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdubois <tdubois@student.42angouleme.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 01:12:17 by tdubois           #+#    #+#             */
/*   Updated: 2023/05/01 20:15:57 by tdubois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENE_OBJECT_H
# define SCENE_OBJECT_H

//> SCENE'S OBJECT MODEL
//>
//> List of objects to be rendered.

# include <minirt/utils/color.h>
# include <minirt/utils/geometry.h>

//----------------------------------------------------------------------------//
//---- SPHERE ----------------------------------------------------------------//

typedef struct s_sphere
{
	t_vec3	pos;
	t_color	color;
	float	diameter;

	float	radius;
	float	radius2;
}	t_sphere;

//----------------------------------------------------------------------------//
//---- PLANE -----------------------------------------------------------------//

typedef struct s_plane
{
	t_vec3	pos;
	t_color	color;
	t_vec3	normal;

	t_vec3	rev_normal;
}	t_plane;

//----------------------------------------------------------------------------//
//---- CYLINDER --------------------------------------------------------------//

typedef struct s_cylinder
{
	t_vec3	pos;
	t_color	color;
	float	radius;
	float	height;
	t_vec3	axis;

	t_plane	bot;
	t_plane	top;
	float	radius2;
}	t_cylinder;

//----------------------------------------------------------------------------//
//---- OBJECT INTERFACE ------------------------------------------------------//

typedef enum e_object_t
{
	OBJ_SPHERE,
	OBJ_PLANE,
	OBJ_CYLINDER,
}	t_object_t;

typedef union u_object_v
{
	t_sphere	as_sphere;
	t_plane		as_plane;
	t_cylinder	as_cylinder;
}	t_object_v;

typedef struct s_object
{
	t_object_t		type;
	t_object_v		value;

	struct s_object	*next;
}	t_object;

#endif//SCENE_OBJECT_H
