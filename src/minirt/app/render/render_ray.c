/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_ray.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdubois <tdubois@student.42angouleme.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 08:17:25 by tdubois           #+#    #+#             */
/*   Updated: 2023/05/10 17:10:27 by tdubois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt/app/app.h>

#include <minirt/scene/scene.h>
#include <stdbool.h>

typedef struct s_intersection
{
	t_object const	*object;
	float			distance;

	t_vec3			pos;
	t_vec3			normal;
}	t_intersection;


////////////////////////////////////////////////////////////////////////////////

#define RGB_BLACK 0x000000FF

int	render_ray(
		t_scene const *scene,
		t_ray const *ray)
{
	t_object const	*intersected_object;
	float			distance;

	intersected_object = 
		fetch_closest_intersection(ray, scene->objects, &distance);
	if (intersected_object == NULL)
		return (RGB_BLACK);
	if (intersected_object->type == OBJ_SPHERE)
		return (render_ray_on_sphere(intersected_object, distance));
	//other object types...
	return (RGB_BLACK);
}
