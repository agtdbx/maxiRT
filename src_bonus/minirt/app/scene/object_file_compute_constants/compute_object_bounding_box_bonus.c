/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compute_object_bounding_box_bonus.c                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auguste <auguste@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 22:51:50 by auguste           #+#    #+#             */
/*   Updated: 2024/03/21 23:05:30 by auguste          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt/app/scene/scene_bonus.h"

#include "minirt/app/utils/geometry/geometry_bonus.h"

#define MIN_SIZE_BBOX 0.05f

static void	calculate_bounding_box_bounds(
				t_object_file *objf,
				float	bounds_x[2],
				float	bounds_y[2],
				float	bounds_z[2]);
static void	set_min_max(
				float const *nb,
				float bounds[2]);
static void	compute_objf_binary_tree(
				t_object_file *objf,
				float	bounds_x[2],
				float	bounds_y[2],
				float	bounds_z[2]);
static void	fill_objf_bbox_tree(
				t_object_binary_part *part,
				char axe);
static void	compute_bounding_box_constants(
				t_object_bounding_box *bounding_box);
//static bool is_polygon_inside_object_bounding_box(
//				t_object_bounding_box *bbox,
//				t_object_polygon *polygon);
//static bool	is_point_inside_object_bounding_box(
//				t_object_bounding_box *bbox,
//				t_vec3 const *point);
//static bool	is_in_bound(
//				float min,
//				float max,
//				float nb);
static bool	is_bbox_too_small(
				t_object_bounding_box *bbox);


static bool is_polygon_inside_object_bounding_box(
				t_object_bounding_box *bbox,
				t_object_polygon *polygon);
static bool is_triangle_inside_object_bounding_box(
				t_vec3 *p1,
				t_vec3 *p2,
				t_vec3 *p3,
				t_object_bounding_box *bbox);
int triBoxOverlap(float boxcenter[3],float boxhalfsize[3],float triverts[3][3]);



void	compute_objf_bounding_boxes(
				t_object_file *objf)
{
	float	bounds_x[2];
	float	bounds_y[2];
	float	bounds_z[2];

	// Get mins and max
	calculate_bounding_box_bounds(objf, bounds_x, bounds_y, bounds_z);

	// Calcultate bounding boxes in binary tree
	compute_objf_binary_tree(objf, bounds_x, bounds_y, bounds_z);
}

static void	calculate_bounding_box_bounds(
				t_object_file *objf,
				float	bounds_x[2],
				float	bounds_y[2],
				float	bounds_z[2])
{
	int	i;

	bounds_x[0] = objf->real_vertices[0].x;
	bounds_y[0] = objf->real_vertices[0].x;
	bounds_z[0] = objf->real_vertices[0].y;
	bounds_x[1] = objf->real_vertices[0].y;
	bounds_y[1] = objf->real_vertices[0].z;
	bounds_z[1] = objf->real_vertices[0].z;
	i = 1;
	while (i < objf->nb_vertices)
	{
		set_min_max(&objf->real_vertices[i].x, bounds_x);
		set_min_max(&objf->real_vertices[i].y, bounds_y);
		set_min_max(&objf->real_vertices[i].z, bounds_z);
		i++;
	}
}

static void	set_min_max(
				float const *nb,
				float bounds[2])
{
	if (bounds[0] > *nb)
		bounds[0] = *nb;
	if (bounds[1] < *nb)
		bounds[1] = *nb;
}

static void	compute_objf_binary_tree(
				t_object_file *objf,
				float	bounds_x[2],
				float	bounds_y[2],
				float	bounds_z[2])
{
	int		i;
	char	axe;

	if (objf->binary_partition != NULL)
	{
		free_object_binary_tree(objf->binary_partition);
		objf->binary_partition = NULL;
	}
	create_new_object_binary_tree_part(&objf->binary_partition);
	if (objf->binary_partition == NULL)
		return ;

	objf->binary_partition->bounding_box.min_x = bounds_x[0];
	objf->binary_partition->bounding_box.min_y = bounds_y[0];
	objf->binary_partition->bounding_box.min_z = bounds_z[0];
	objf->binary_partition->bounding_box.max_x = bounds_x[1];
	objf->binary_partition->bounding_box.max_y = bounds_y[1];
	objf->binary_partition->bounding_box.max_z = bounds_z[1];

	compute_bounding_box_constants(&objf->binary_partition->bounding_box);

	i = 0;
	while (i < objf->nb_polygons)
	{
		add_object_binary_polygons(
			&objf->binary_partition->polygons,
			&objf->polygons[i], i);
		i++;
	}

	axe = 'x';
	if (objf->binary_partition->polygons != NULL
		&& objf->nb_polygons > 0
		&& ! is_bbox_too_small(&objf->binary_partition->bounding_box))
	{
		fill_objf_bbox_tree(objf->binary_partition, axe);
	}
}


static void	fill_objf_bbox_tree(
				t_object_binary_part *part,
				char axe)
{
	int						child_1_polygons;
	int						child_2_polygons;
	float					mid_axe;
	t_object_binary_part	*child_1;
	t_object_binary_part	*child_2;
	t_object_binary_polygon	*actual;

	if (part->polygons == NULL || part->polygons->next == NULL
		|| is_bbox_too_small(&part->bounding_box))
		return ;

	create_new_object_binary_tree_part(&child_1);
	if (child_1 == NULL)
		return ;
	create_new_object_binary_tree_part(&child_2);
	if (child_2 == NULL)
	{
		free_object_binary_tree(child_1);
		return ;
	}

	// Cut main bbox in half by axe to childs have bbox
	if (axe == 'x')
	{
		// Calculate mid axe
		mid_axe = part->bounding_box.max_x - part->bounding_box.min_x;
		mid_axe /= 2.0f;
		mid_axe += part->bounding_box.min_x;

		// Assign mins and max to childs
		child_1->bounding_box.min_x = mid_axe;
		child_2->bounding_box.min_x = part->bounding_box.min_x;
		child_1->bounding_box.max_x = part->bounding_box.max_x;
		child_2->bounding_box.max_x = mid_axe;

		child_1->bounding_box.min_y = part->bounding_box.min_y;
		child_2->bounding_box.min_y = part->bounding_box.min_y;
		child_1->bounding_box.max_y = part->bounding_box.max_y;
		child_2->bounding_box.max_y = part->bounding_box.max_y;

		child_1->bounding_box.min_z = part->bounding_box.min_z;
		child_2->bounding_box.min_z = part->bounding_box.min_z;
		child_1->bounding_box.max_z = part->bounding_box.max_z;
		child_2->bounding_box.max_z = part->bounding_box.max_z;

		axe = 'y';
	}
	else if (axe == 'y')
	{
		// Calculate mid axe
		mid_axe = part->bounding_box.max_y - part->bounding_box.min_y;
		mid_axe /= 2.0f;
		mid_axe += part->bounding_box.min_y;

		// Assign mins and max to childs
		child_1->bounding_box.min_x = part->bounding_box.min_x;
		child_2->bounding_box.min_x = part->bounding_box.min_x;
		child_1->bounding_box.max_x = part->bounding_box.max_x;
		child_2->bounding_box.max_x = part->bounding_box.max_x;

		child_1->bounding_box.min_y = mid_axe;
		child_2->bounding_box.min_y = part->bounding_box.min_y;
		child_1->bounding_box.max_y = part->bounding_box.max_y;
		child_2->bounding_box.max_y = mid_axe;

		child_1->bounding_box.min_z = part->bounding_box.min_z;
		child_2->bounding_box.min_z = part->bounding_box.min_z;
		child_1->bounding_box.max_z = part->bounding_box.max_z;
		child_2->bounding_box.max_z = part->bounding_box.max_z;

		axe = 'z';
	}
	else
	{
		// Calculate mid axe
		mid_axe = part->bounding_box.max_z - part->bounding_box.min_z;
		mid_axe /= 2.0f;
		mid_axe += part->bounding_box.min_z;

		// Assign mins and max to childs
		child_1->bounding_box.min_x = part->bounding_box.min_x;
		child_2->bounding_box.min_x = part->bounding_box.min_x;
		child_1->bounding_box.max_x = part->bounding_box.max_x;
		child_2->bounding_box.max_x = part->bounding_box.max_x;

		child_1->bounding_box.min_y = part->bounding_box.min_y;
		child_2->bounding_box.min_y = part->bounding_box.min_y;
		child_1->bounding_box.max_y = part->bounding_box.max_y;
		child_2->bounding_box.max_y = part->bounding_box.max_y;

		child_1->bounding_box.min_z = mid_axe;
		child_2->bounding_box.min_z = part->bounding_box.min_z;
		child_1->bounding_box.max_z = part->bounding_box.max_z;
		child_2->bounding_box.max_z = mid_axe;

		axe = 'x';
	}

	// Compute bbox constants for childs
	compute_bounding_box_constants(&child_1->bounding_box);
	compute_bounding_box_constants(&child_2->bounding_box);

	// Iterate thought each polygon of main tree part
	child_1_polygons = 0;
	child_2_polygons = 0;
	actual = part->polygons;

	while (actual)
	{
		if (is_polygon_inside_object_bounding_box(
				&child_1->bounding_box, actual->polygon))
		{
			add_object_binary_polygons(
				&child_1->polygons, actual->polygon, actual->polygon_id);
			child_1_polygons++;
		}

		if (is_polygon_inside_object_bounding_box(
				&child_2->bounding_box, actual->polygon))
		{
			add_object_binary_polygons(
				&child_2->polygons, actual->polygon, actual->polygon_id);
			child_2_polygons++;
		}

		actual = actual->next;
	}

	// Free the useless polygons chain list (now polygons are in childs)
	free_object_binary_polygons(part->polygons);
	part->polygons = NULL;

	part->child_1 = child_1;
	part->child_2 = child_2;

	fill_objf_bbox_tree(child_1, axe);
	fill_objf_bbox_tree(child_2, axe);
}

static void	compute_bounding_box_constants(
				t_object_bounding_box *bbox)
{
	float	inv_width;
	float	inv_height;
	float	inv_depth;
	t_vec3	p_ruf;
	t_vec3	p_luf;
	t_vec3	p_rdf;
	t_vec3	p_ldf;
	t_vec3	p_rub;
	t_vec3	p_lub;
	t_vec3	p_rdb;
	t_vec3	p_ldb;

	// Calculate inv_size
	inv_width = bbox->max_x - bbox->min_x;
	if (inv_width != 0.0f)
		inv_width = 1.0f / inv_width;
	inv_height = bbox->max_y - bbox->min_y;
	if (inv_height != 0.0f)
		inv_height = 1.0f / inv_height;
	inv_depth = bbox->max_z - bbox->min_z;
	if (inv_depth != 0.0f)
		inv_depth = 1.0f / inv_depth;

	// Calculate points
	p_ruf = (t_vec3){bbox->max_x, bbox->max_y, bbox->max_z};
	p_luf = (t_vec3){bbox->min_x, bbox->max_y, bbox->max_z};
	p_rdf = (t_vec3){bbox->max_x, bbox->min_y, bbox->max_z};
	p_ldf = (t_vec3){bbox->min_x, bbox->min_y, bbox->max_z};
	p_rub = (t_vec3){bbox->max_x, bbox->max_y, bbox->min_z};
	p_lub = (t_vec3){bbox->min_x, bbox->max_y, bbox->min_z};
	p_rdb = (t_vec3){bbox->max_x, bbox->min_y, bbox->min_z};
	p_ldb = (t_vec3){bbox->min_x, bbox->min_y, bbox->min_z};

	// right face
	bbox->right.normal = (t_vec3){1.0f, 0.0f, 0.0f};
	bbox->right.inv_width = inv_depth;
	bbox->right.inv_height = inv_height;
	bbox->right.point_ru = p_rub;
	bbox->right.point_lu = p_ruf;
	bbox->right.point_rd = p_rdb;
	bbox->right.point_ld = p_rdf;

	// left faceS
	bbox->left.normal = (t_vec3){-1.0f, 0.0f, 0.0f};
	bbox->left.inv_width = inv_depth;
	bbox->left.inv_height = inv_height;
	bbox->left.point_ru = p_lub;
	bbox->left.point_lu = p_luf;
	bbox->left.point_rd = p_ldb;
	bbox->left.point_ld = p_ldf;

	// up face
	bbox->up.normal = (t_vec3){0.0f, 1.0f, 0.0f};
	bbox->up.inv_width = inv_width;
	bbox->up.inv_height = inv_depth;
	bbox->up.point_ru = p_rub;
	bbox->up.point_lu = p_lub;
	bbox->up.point_rd = p_ruf;
	bbox->up.point_ld = p_luf;

	// down face
	bbox->down.normal = (t_vec3){0.0f, -1.0f, 0.0f};
	bbox->down.inv_width = inv_width;
	bbox->down.inv_height = inv_depth;
	bbox->down.point_ru = p_rdb;
	bbox->down.point_lu = p_ldb;
	bbox->down.point_rd = p_rdf;
	bbox->down.point_ld = p_ldf;

	// front face
	bbox->front.normal = (t_vec3){0.0f, 0.0f, 1.0f};
	bbox->front.inv_width = inv_width;
	bbox->front.inv_height = inv_height;
	bbox->front.point_ru = p_ruf;
	bbox->front.point_lu = p_luf;
	bbox->front.point_rd = p_rdf;
	bbox->front.point_ld = p_ldf;

	// back face
	bbox->back.normal = (t_vec3){0.0f, 0.0f, -1.0f};
	bbox->back.inv_width = inv_width;
	bbox->back.inv_height = inv_height;
	bbox->back.point_ru = p_rub;
	bbox->back.point_lu = p_lub;
	bbox->back.point_rd = p_rdb;
	bbox->back.point_ld = p_ldb;
}

//static bool is_polygon_inside_object_bounding_box(
//				t_object_bounding_box *bbox,
//				t_object_polygon *polygon)
//{
//	if (polygon->type == OBJF_TRIANGLE)
//		return (is_point_inside_object_bounding_box(
//					bbox, &polygon->value.as_objf_triangle.point1)
//				|| is_point_inside_object_bounding_box(
//					bbox, &polygon->value.as_objf_triangle.point2)
//				|| is_point_inside_object_bounding_box(
//					bbox, &polygon->value.as_objf_triangle.point3));
//	if (polygon->type == OBJF_RECTANGLE)
//		return (is_point_inside_object_bounding_box(
//					bbox, &polygon->value.as_objf_rectangle.point1)
//				|| is_point_inside_object_bounding_box(
//					bbox, &polygon->value.as_objf_rectangle.point2)
//				|| is_point_inside_object_bounding_box(
//					bbox, &polygon->value.as_objf_rectangle.point3)
//				|| is_point_inside_object_bounding_box(
//					bbox, &polygon->value.as_objf_rectangle.point4));
//	return (false);
//}

//static bool	is_point_inside_object_bounding_box(
//				t_object_bounding_box *bbox,
//				t_vec3 const *point)
//{
//	if (!is_in_bound(
//			bbox->min_x,
//			bbox->max_x,
//			point->x))
//		return (false);
//	if (!is_in_bound(
//			bbox->min_y,
//			bbox->max_y,
//			point->y))
//		return (false);
//	if (!is_in_bound(
//			bbox->min_z,
//			bbox->max_z,
//			point->z))
//		return (false);
//	return (true);
//}


//static bool	is_in_bound(
//				float min,
//				float max,
//				float nb)
//{
//	return (min <= nb && nb <= max);
//}


static bool	is_bbox_too_small(
				t_object_bounding_box *bbox)
{
	return ((bbox->max_x - bbox->min_x) < MIN_SIZE_BBOX
		|| (bbox->max_y - bbox->min_y) < MIN_SIZE_BBOX
		|| (bbox->max_z - bbox->min_z) < MIN_SIZE_BBOX);
}





static bool is_polygon_inside_object_bounding_box(
				t_object_bounding_box *bbox,
				t_object_polygon *polygon)
{
	if (polygon->type == OBJF_TRIANGLE)
	{
		return (is_triangle_inside_object_bounding_box(
					&polygon->value.as_objf_triangle.point1,
					&polygon->value.as_objf_triangle.point2,
					&polygon->value.as_objf_triangle.point3,
					bbox));
	}
	if (polygon->type == OBJF_RECTANGLE)
	{
		return (is_triangle_inside_object_bounding_box(
					&polygon->value.as_objf_rectangle.point1,
					&polygon->value.as_objf_rectangle.point2,
					&polygon->value.as_objf_rectangle.point3,
					bbox)
				|| is_triangle_inside_object_bounding_box(
					&polygon->value.as_objf_rectangle.point1,
					&polygon->value.as_objf_rectangle.point3,
					&polygon->value.as_objf_rectangle.point4,
					bbox));
	}
	return (false);
}

static bool is_triangle_inside_object_bounding_box(
				t_vec3 *p1,
				t_vec3 *p2,
				t_vec3 *p3,
				t_object_bounding_box *bbox)

{
	float boxcenter[3];
	float boxhalfsize[3];
	float triverts[3][3];

	boxhalfsize[0] = (bbox->max_x - bbox->min_x) / 2.0f;
	boxhalfsize[1] = (bbox->max_y - bbox->min_y) / 2.0f;
	boxhalfsize[2] = (bbox->max_z - bbox->min_z) / 2.0f;

	boxcenter[0] = bbox->min_x + boxhalfsize[0];
	boxcenter[1] = bbox->min_y + boxhalfsize[1];
	boxcenter[2] = bbox->min_z + boxhalfsize[2];

	triverts[0][0] = p1->x;
	triverts[0][1] = p1->y;
	triverts[0][2] = p1->z;

	triverts[1][0] = p2->x;
	triverts[1][1] = p2->y;
	triverts[1][2] = p2->z;

	triverts[2][0] = p3->x;
	triverts[2][1] = p3->y;
	triverts[2][2] = p3->z;

	return (triBoxOverlap(boxcenter, boxhalfsize, triverts));
}








#include <math.h>

#define X 0
#define Y 1
#define Z 2

#define CROSS(dest,v1,v2) \
          dest[0]=v1[1]*v2[2]-v1[2]*v2[1]; \
          dest[1]=v1[2]*v2[0]-v1[0]*v2[2]; \
          dest[2]=v1[0]*v2[1]-v1[1]*v2[0];

#define DOT(v1,v2) (v1[0]*v2[0]+v1[1]*v2[1]+v1[2]*v2[2])

#define SUB(dest,v1,v2) \
          dest[0]=v1[0]-v2[0]; \
          dest[1]=v1[1]-v2[1]; \
          dest[2]=v1[2]-v2[2];

#define FINDMINMAX(x0,x1,x2,min,max) \
  min = max = x0;   \
  if(x1<min) min=x1;\
  if(x1>max) max=x1;\
  if(x2<min) min=x2;\
  if(x2>max) max=x2;

int planeBoxOverlap(float normal[3],float d, float maxbox[3])
{
  int q;
  float vmin[3],vmax[3];
  for(q=X;q<=Z;q++)
  {
    if(normal[q]>0.0f)
    {
      vmin[q]=-maxbox[q];
      vmax[q]=maxbox[q];
    }
    else
    {
      vmin[q]=maxbox[q];
      vmax[q]=-maxbox[q];
    }
  }
  if(DOT(normal,vmin)+d>0.0f) return 0;
  if(DOT(normal,vmax)+d>=0.0f) return 1;

  return 0;
}


/*======================== X-tests ========================*/
#define AXISTEST_X01(a, b, fa, fb)             \
    p0 = a*v0[Y] - b*v0[Z];                    \
    p2 = a*v2[Y] - b*v2[Z];                    \
        if(p0<p2) {min=p0; max=p2;} else {min=p2; max=p0;} \
    rad = fa * boxhalfsize[Y] + fb * boxhalfsize[Z];   \
    if(min>rad || max<-rad) return 0;

#define AXISTEST_X2(a, b, fa, fb)              \
    p0 = a*v0[Y] - b*v0[Z];                    \
    p1 = a*v1[Y] - b*v1[Z];                    \
        if(p0<p1) {min=p0; max=p1;} else {min=p1; max=p0;} \
    rad = fa * boxhalfsize[Y] + fb * boxhalfsize[Z];   \
    if(min>rad || max<-rad) return 0;

/*======================== Y-tests ========================*/
#define AXISTEST_Y02(a, b, fa, fb)             \
    p0 = -a*v0[X] + b*v0[Z];                   \
    p2 = -a*v2[X] + b*v2[Z];                       \
        if(p0<p2) {min=p0; max=p2;} else {min=p2; max=p0;} \
    rad = fa * boxhalfsize[X] + fb * boxhalfsize[Z];   \
    if(min>rad || max<-rad) return 0;

#define AXISTEST_Y1(a, b, fa, fb)              \
    p0 = -a*v0[X] + b*v0[Z];                   \
    p1 = -a*v1[X] + b*v1[Z];                       \
        if(p0<p1) {min=p0; max=p1;} else {min=p1; max=p0;} \
    rad = fa * boxhalfsize[X] + fb * boxhalfsize[Z];   \
    if(min>rad || max<-rad) return 0;

/*======================== Z-tests ========================*/

#define AXISTEST_Z12(a, b, fa, fb)             \
    p1 = a*v1[X] - b*v1[Y];                    \
    p2 = a*v2[X] - b*v2[Y];                    \
        if(p2<p1) {min=p2; max=p1;} else {min=p1; max=p2;} \
    rad = fa * boxhalfsize[X] + fb * boxhalfsize[Y];   \
    if(min>rad || max<-rad) return 0;

#define AXISTEST_Z0(a, b, fa, fb)              \
    p0 = a*v0[X] - b*v0[Y];                \
    p1 = a*v1[X] - b*v1[Y];                    \
        if(p0<p1) {min=p0; max=p1;} else {min=p1; max=p0;} \
    rad = fa * boxhalfsize[X] + fb * boxhalfsize[Y];   \
    if(min>rad || max<-rad) return 0;

int triBoxOverlap(float boxcenter[3],float boxhalfsize[3],float triverts[3][3])
{

  /*    use separating axis theorem to test overlap between triangle and box */
  /*    need to test for overlap in these directions: */
  /*    1) the {x,y,z}-directions (actually, since we use the AABB of the triangle */
  /*       we do not even need to test these) */
  /*    2) normal of the triangle */
  /*    3) crossproduct(edge from tri, {x,y,z}-directin) */
  /*       this gives 3x3=9 more tests */
   float v0[3],v1[3],v2[3];
   float min,max,d,p0,p1,p2,rad,fex,fey,fez;
   float normal[3],e0[3],e1[3],e2[3];

   /* This is the fastest branch on Sun */
   /* move everything so that the boxcenter is in (0,0,0) */
   SUB(v0,triverts[0],boxcenter);
   SUB(v1,triverts[1],boxcenter);
   SUB(v2,triverts[2],boxcenter);

   /* compute triangle edges */
   SUB(e0,v1,v0);      /* tri edge 0 */
   SUB(e1,v2,v1);      /* tri edge 1 */
   SUB(e2,v0,v2);      /* tri edge 2 */

   /* Bullet 3:  */
   /*  test the 9 tests first (this was faster) */
   fex = fabs(e0[X]);
   fey = fabs(e0[Y]);
   fez = fabs(e0[Z]);
   AXISTEST_X01(e0[Z], e0[Y], fez, fey);
   AXISTEST_Y02(e0[Z], e0[X], fez, fex);
   AXISTEST_Z12(e0[Y], e0[X], fey, fex);

   fex = fabs(e1[X]);
   fey = fabs(e1[Y]);
   fez = fabs(e1[Z]);
   AXISTEST_X01(e1[Z], e1[Y], fez, fey);
   AXISTEST_Y02(e1[Z], e1[X], fez, fex);
   AXISTEST_Z0(e1[Y], e1[X], fey, fex);

   fex = fabs(e2[X]);
   fey = fabs(e2[Y]);
   fez = fabs(e2[Z]);
   AXISTEST_X2(e2[Z], e2[Y], fez, fey);
   AXISTEST_Y1(e2[Z], e2[X], fez, fex);
   AXISTEST_Z12(e2[Y], e2[X], fey, fex);

   /* Bullet 1: */
   /*  first test overlap in the {x,y,z}-directions */
   /*  find min, max of the triangle each direction, and test for overlap in */
   /*  that direction -- this is equivalent to testing a minimal AABB around */
   /*  the triangle against the AABB */

   /* test in X-direction */
   FINDMINMAX(v0[X],v1[X],v2[X],min,max);
   if(min>boxhalfsize[X] || max<-boxhalfsize[X]) return 0;

   /* test in Y-direction */
   FINDMINMAX(v0[Y],v1[Y],v2[Y],min,max);
   if(min>boxhalfsize[Y] || max<-boxhalfsize[Y]) return 0;

   /* test in Z-direction */
   FINDMINMAX(v0[Z],v1[Z],v2[Z],min,max);
   if(min>boxhalfsize[Z] || max<-boxhalfsize[Z]) return 0;

   /* Bullet 2: */
   /*  test if the box intersects the plane of the triangle */
   /*  compute plane equation of triangle: normal*x+d=0 */
   CROSS(normal,e0,e1);
   d=-DOT(normal,v0);  /* plane eq: normal.x+d=0 */
   if(!planeBoxOverlap(normal,d,boxhalfsize)) return 0;

   return 1;   /* box and triangle overlaps */
}
