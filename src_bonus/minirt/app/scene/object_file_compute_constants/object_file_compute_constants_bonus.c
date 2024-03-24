/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_file_compute_constants_bonus.c              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auguste <auguste@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 19:51:32 by aderouba          #+#    #+#             */
/*   Updated: 2024/03/24 11:22:35 by auguste          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt/app/scene/scene_bonus.h"

#include <math.h>

#include "minirt/app/utils/geometry/geometry_bonus.h"

static void	axis_checker(
				t_object_file *objf);
static void	compute_objf_vertices(
				t_object_file *objf);
static void	compute_objf_polygons(
				t_object_file *objf);


#include <stdio.h>

//static void	print_polygon(
//				t_object_polygon *polygon)
//{
//	if (polygon == NULL)
//		printf("[POLY NULL]\n");
//	else if (polygon->type == OBJ_TRIANGLE)
//		printf("tri  |% .2f, % .2f, % .2f| |% .2f, % .2f, % .2f| |% .2f, % .2f, % .2f|\n",
//			polygon->value.as_objf_triangle.point1.x,
//			polygon->value.as_objf_triangle.point1.y,
//			polygon->value.as_objf_triangle.point1.z,
//			polygon->value.as_objf_triangle.point2.x,
//			polygon->value.as_objf_triangle.point2.y,
//			polygon->value.as_objf_triangle.point2.z,
//			polygon->value.as_objf_triangle.point3.x,
//			polygon->value.as_objf_triangle.point3.y,
//			polygon->value.as_objf_triangle.point3.z);
//	else
//		printf("rect |% .2f, % .2f, % .2f| |% .2f, % .2f, % .2f| |% .2f, % .2f, % .2f| |% .2f, % .2f, % .2f|\n",
//			polygon->value.as_objf_rectangle.point1.x,
//			polygon->value.as_objf_rectangle.point1.y,
//			polygon->value.as_objf_rectangle.point1.z,
//			polygon->value.as_objf_rectangle.point2.x,
//			polygon->value.as_objf_rectangle.point2.y,
//			polygon->value.as_objf_rectangle.point2.z,
//			polygon->value.as_objf_rectangle.point3.x,
//			polygon->value.as_objf_rectangle.point3.y,
//			polygon->value.as_objf_rectangle.point3.z,
//			polygon->value.as_objf_rectangle.point4.x,
//			polygon->value.as_objf_rectangle.point4.y,
//			polygon->value.as_objf_rectangle.point4.z);
//}

//static void	print_polygons_list(
//				t_object_binary_polygon *polygons)
//{
//	t_object_binary_polygon *actual;

//	printf("POLYGONS :\n");
//	actual = polygons;
//	if (actual == NULL)
//	{
//		printf("{NULL}\n");
//		return ;
//	}

//	while (actual)
//	{
//		print_polygon(actual->polygon);
//		actual = actual->next;
//	}
//}

//static void	print_tree_part(
//				t_object_binary_part *part)
//{
//	if (part == NULL)
//	{
//		printf("PART NULL\n");
//		return ;
//	}
//	printf("PART OK\n");

//	if (part->child_1 == NULL)
//		printf("CHILD 1 NULL\n");
//	else
//		printf("CHILD 1 OK\n");

//	if (part->child_2 == NULL)
//		printf("CHILD 2 NULL\n");
//	else
//		printf("CHILD 2 OK\n");

//	print_polygons_list(part->polygons);
//}


/**
 * Compute constants from object file properties to facilitate further
 * calculations
 * @param[out] objf
 */
void	object_file_compute_constants(
			t_object_file *objf)
{
	printf("OBJ{vertices : %i, polygons : %i}\n",
			objf->nb_vertices, objf->nb_polygons);

	axis_checker(objf);

	vec3_cross(&objf->x_axis, &objf->y_axis, &objf->z_axis);
	vec3_normalize(&objf->x_axis);
	vec3_normalize(&objf->y_axis);
	vec3_normalize(&objf->z_axis);
	printf("axis done, start of vertices compute\n");

	// Compute all vertices
	compute_objf_vertices(objf);
	printf("vertices done, start of polygons compute\n");

	// Compute all polygons
	compute_objf_polygons(objf);
	printf("polygons done, start of bounding box tree compute\n");

	// Compute bounding boxes
	compute_objf_bounding_boxes(objf);
	printf("bounding vox tree done\n");

	//print_tree_part(objf->binary_partition);
}


static void	axis_checker(
				t_object_file *objf)
{
	if (vec3_dot(&objf->x_axis, &objf->y_axis) != 0.0f)
	{
		if (vec3_dot(&objf->x_axis, &objf->z_axis) != 0.0f)
			vec3_cross(&objf->y_axis, &objf->z_axis, &objf->x_axis);
		else
			vec3_cross(&objf->x_axis, &objf->z_axis, &objf->y_axis);
	}
}


static void	compute_objf_vertices(
				t_object_file *objf)
{
	int	i;

	i = 0;
	while (i < objf->nb_vertices)
	{
		objf->real_vertices[i] = objf->vertices[i];
		// Scale points
		vec3_scale(&objf->real_vertices[i], objf->size);
		// Rotate points along objf axis
		objf->real_vertices[i] = mat_product(&objf->x_axis, &objf->y_axis,
									&objf->z_axis, &objf->real_vertices[i]);
		// Move points along objf position
		vec3_add(&objf->real_vertices[i], &objf->pos);
		i++;
	}
}

static void	compute_objf_polygons(
				t_object_file *objf)
{
	int	i;

	i = 0;
	while (i < objf->nb_polygons)
	{
		if (objf->polygons[i].type == OBJF_TRIANGLE)
			compute_objf_triangle(objf, &objf->polygons[i].value.as_objf_triangle);
		else if (objf->polygons[i].type == OBJF_RECTANGLE)
			compute_objf_rectangle(objf, &objf->polygons[i].value.as_objf_rectangle);
		i++;
	}
}
