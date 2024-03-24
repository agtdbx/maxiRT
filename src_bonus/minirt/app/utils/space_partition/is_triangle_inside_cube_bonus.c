/* ************************************************************************** */
/*																																						*/
/*																												:::			::::::::	 */
/*	 is_triangle_inside_cube_bonus.c										:+:			:+:		:+:	 */
/*																										+:+ +:+				 +:+		 */
/*	 By: auguste <auguste@student.42.fr>						+#+	+:+			 +#+				*/
/*																								+#+#+#+#+#+	 +#+					 */
/*	 Created: 2024/03/23 14:36:50 by auguste					 #+#		#+#						 */
/*	 Updated: 2024/03/23 15:35:09 by auguste					###	 ########.fr			 */
/*																																						*/
/* ************************************************************************** */

#include "minirt/app/scene/scene_bonus.h"

#include "minirt/app/utils/geometry/geometry_bonus.h"

#include "minirt/app/utils/space_partition/space_partition.h"

#include <math.h>

static bool	ax_is_test_x01(
				float a,
				float b,
				float fa,
				float fb,
				t_vec3 const *v0,
				t_vec3 const *v2,
				t_bounding_box const *bbox);
static bool	ax_is_test_x2(
				float a,
				float b,
				float fa,
				float fb,
				t_vec3 const *v0,
				t_vec3 const *v1,
				t_bounding_box const *bbox);
static bool	ax_is_test_y02(
				float a,
				float b,
				float fa,
				float fb,
				t_vec3 const *v0,
				t_vec3 const *v2,
				t_bounding_box const *bbox);
static bool	ax_is_test_y1(
				float a,
				float b,
				float fa,
				float fb,
				t_vec3 const *v0,
				t_vec3 const *v1,
				t_bounding_box const *bbox);
static bool	ax_is_test_z12(
				float a,
				float b,
				float fa,
				float fb,
				t_vec3 const *v1,
				t_vec3 const *v2,
				t_bounding_box const *bbox);
static bool	ax_is_test_z0(
				float a,
				float b,
				float fa,
				float fb,
				t_vec3 const *v0,
				t_vec3 const *v1,
				t_bounding_box const *bbox);
static bool	plane_box_overlap(
				t_vec3 const *normal,
				float d,
				t_bounding_box const *bbox);
static void	find_min_max(
				float x0,
				float x1,
				float x2,
				float *min,
				float *max);


bool	is_triangle_collide_cube(
			t_vec3 const *p1,
			t_vec3 const *p2,
			t_vec3 const *p3,
			t_vec3 const *normal,
			t_bounding_box const *bbox)
{
	t_vec3	v0;
	t_vec3	v1;
	t_vec3	v2;
	t_vec3	e0;
	t_vec3	e1;
	t_vec3	e2;
	float	fex;
	float	fey;
	float	fez;
	float	min;
	float	max;
	float	d;
	/*		use separating axis theorem to test overlap between triangle and box */
	/*		need to test for overlap in these directions: */
	/*		1) the {x,y,z}-directions (actually, since we use the AABB of the triangle */
	/*			 we do not even need to test these) */
	/*		2) normal of the triangle */
	/*		3) crossproduct(edge from tri, {x,y,z}-directin) */
	/*			 this gives 3x3=9 more tests */

	// Point pos in box center coordonate
	vec3_substract_into(&v0, p1, &bbox->center);
	vec3_substract_into(&v1, p2, &bbox->center);
	vec3_substract_into(&v2, p3, &bbox->center);

	// Compute edges of triangles
	vec3_substract_into(&e0, &v1, &v0);
	vec3_substract_into(&e1, &v2, &v1);
	vec3_substract_into(&e2, &v0, &v2);

	/* Bullet 3:	*/
	/*	test the 9 tests first (this was faster) */
	fex = fabs(e0.x);
	fey = fabs(e0.y);
	fez = fabs(e0.z);
	if (!ax_is_test_x01(e0.z, e0.y, fez, fey, &v0, &v2, bbox))
		return (false);
	if (!ax_is_test_y02(e0.z, e0.x, fez, fex, &v0, &v2, bbox))
		return (false);
	if (!ax_is_test_z12(e0.y, e0.x, fey, fex, &v1, &v2, bbox))
		return (false);

	fex = fabs(e1.x);
	fey = fabs(e1.y);
	fez = fabs(e1.z);
	if (!ax_is_test_x01(e1.z, e1.y, fez, fey, &v0, &v2, bbox))
		return (false);
	if (!ax_is_test_y02(e1.z, e1.x, fez, fex, &v0, &v2, bbox))
		return (false);
	if (!ax_is_test_z0(e1.y, e1.x, fey, fex, &v0, &v1, bbox))
		return (false);

	fex = fabs(e2.x);
	fey = fabs(e2.y);
	fez = fabs(e2.z);
	if (!ax_is_test_x2(e2.z, e2.y, fez, fey, &v0, &v1, bbox))
		return (false);
	if (!ax_is_test_y1(e2.z, e2.x, fez, fex, &v0, &v1, bbox))
		return (false);
	if (!ax_is_test_z12(e2.y, e2.x, fey, fex, &v1, &v2, bbox))
		return (false);

	/* Bullet 1: */
	/*	first test overlap in the {x,y,z}-directions */
	/*	find min, max of the triangle each direction, and test for overlap in */
	/*	that direction -- this is equivalent to testing a minimal AABB around */
	/*	the triangle against the AABB */

	/* test in X-direction */
	find_min_max(v0.x, v1.x, v2.x, &min, &max);
	if (min > bbox->half_width || max < -bbox->half_width)
		return (false);

	/* test in Y-direction */
	find_min_max(v0.y, v1.y, v2.y, &min, &max);
	if (min > bbox->half_height || max < -bbox->half_height)
		return (false);

	/* test in Z-direction */
	find_min_max(v0.z, v1.z, v2.z, &min, &max);
	if (min > bbox->half_depth || max < -bbox->half_depth)
		return (false);

	/* Bullet 2: */
	/*	test if the box intersects the plane of the triangle */
	/*	compute plane equation of triangle: normal*x+d=0 */
	d = vec3_dot(normal, &v0);
	if (!plane_box_overlap(normal, d, bbox))
		return (false);

	return (true);
}


static void	set_min_max(
				float nb1,
				float nb2,
				float *min,
				float *max)
{
	if (nb1 < nb2)
	{
		*min = nb1;
		*max = nb2;
	}
	else
	{
		*min = nb2;
		*max = nb1;
	}
}


static bool	ax_is_test_x01(
				float a,
				float b,
				float fa,
				float fb,
				t_vec3 const *v0,
				t_vec3 const *v2,
				t_bounding_box const *bbox)
{
	float	p0;
	float	p2;
	float	min;
	float	max;
	float	rad;

	p0 = a * v0->y - b * v0->z;
	p2 = a * v2->y - b * v2->z;

	set_min_max(p0, p2, &min, &max);

	rad = fa * bbox->half_height + fb * bbox->half_depth;
	if (min > rad || max < -rad)
		return (false);
	return (true);
}


static bool	ax_is_test_x2(
				float a,
				float b,
				float fa,
				float fb,
				t_vec3 const *v0,
				t_vec3 const *v1,
				t_bounding_box const *bbox)
{
	float	p0;
	float	p1;
	float	min;
	float	max;
	float	rad;

	p0 = (a * v0->y) - (b * v0->z);
	p1 = (a * v1->y) - (b * v1->z);
	set_min_max(p0, p1, &min, &max);
	rad = (fa * bbox->half_height) + (fb * bbox->half_depth);
	if (min > rad || max < -rad)
		return (false);
	return (true);
}


static bool	ax_is_test_y02(
				float a,
				float b,
				float fa,
				float fb,
				t_vec3 const *v0,
				t_vec3 const *v2,
				t_bounding_box const *bbox)
{
	float	p0;
	float	p2;
	float	min;
	float	max;
	float	rad;

	p0 = -(a * v0->x) + (b * v0->z);
	p2 = -(a * v2->x) + (b * v2->z);
	set_min_max(p0, p2, &min, &max);
	rad = (fa * bbox->half_width) + (fb * bbox->half_depth);
	if (min > rad || max < -rad)
		return (false);
	return (true);
}


static bool	ax_is_test_y1(
				float a,
				float b,
				float fa,
				float fb,
				t_vec3 const *v0,
				t_vec3 const *v1,
				t_bounding_box const *bbox)
{
	float	p0;
	float	p1;
	float	min;
	float	max;
	float	rad;

	p0 = -(a * v0->x) + (b * v0->z);
	p1 = -(a * v1->x) + (b * v1->z);
	set_min_max(p0, p1, &min, &max);
	rad = (fa * bbox->half_width) + (fb * bbox->half_depth);
	if (min > rad || max < -rad)
		return (false);
	return (true);
}


static bool	ax_is_test_z12(
				float a,
				float b,
				float fa,
				float fb,
				t_vec3 const *v1,
				t_vec3 const *v2,
				t_bounding_box const *bbox)
{
	float	p1;
	float	p2;
	float	min;
	float	max;
	float	rad;

	p1 = (a * v1->x) - (b * v1->y);
	p2 = (a * v2->x) - (b * v2->y);
	set_min_max(p1, p2, &min, &max);
	rad = (fa * bbox->half_width) + (fb * bbox->half_height);
	if (min > rad || max < -rad)
		return (false);
	return (true);
}


static bool	ax_is_test_z0(
				float a,
				float b,
				float fa,
				float fb,
				t_vec3 const *v0,
				t_vec3 const *v1,
				t_bounding_box const *bbox)
{
	float	p0;
	float	p1;
	float	min;
	float	max;
	float	rad;

	p0 = (a * v0->x) - (b * v0->y);
	p1 = (a * v1->x) - (b * v1->y);
	set_min_max(p0, p1, &min, &max);
	rad = (fa * bbox->half_width) + (fb * bbox->half_height);
	if (min > rad || max < -rad)
		return (false);
	return (true);
}


static bool	plane_box_overlap(
				t_vec3 const *normal,
				float d,
				t_bounding_box const *bbox)
{
	t_vec3	vmin;
	t_vec3	vmax;

	if (normal->x > 0.0f)
	{
		vmin.x = -bbox->half_width;
		vmax.x = bbox->half_width;
	}
	else
	{
		vmin.x = bbox->half_width;
		vmax.x = -bbox->half_width;
	}

	if (normal->y > 0.0f)
	{
		vmin.y = -bbox->half_height;
		vmax.y = bbox->half_height;
	}
	else
	{
		vmin.y = bbox->half_height;
		vmax.y = -bbox->half_height;
	}

	if (normal->z > 0.0f)
	{
		vmin.z = -bbox->half_depth;
		vmax.z = bbox->half_depth;
	}
	else
	{
		vmin.z = bbox->half_depth;
		vmax.z = -bbox->half_depth;
	}

	if (vec3_dot(normal, &vmin) + d > 0.0f)
		return (false);

	if (vec3_dot(normal, &vmax) + d >= 0.0f)
		return (true);

	return (false);
}


static void	find_min_max(
				float x0,
				float x1,
				float x2,
				float *min,
				float *max)
{
	*min = x0;
	*max = x0;

	if (x1 < *min)
		*min = x1;
	if (x2 < *min)
		*min = x2;
	if (x1 > *max)
		*max = x1;
	if (x2 > *max)
		*max = x2;
}
