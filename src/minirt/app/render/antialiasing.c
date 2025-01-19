/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   antialiasing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damien <damien@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 21:47:01 by damien            #+#    #+#             */
/*   Updated: 2025/01/19 01:03:26 by damien           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt/app/app.h"
#include "minirt/app/utils/color/color.h"
#include "minirt/app/render/antialiasing.h"

static t_vec3	_get_pixel_color(mlx_image_t *img, t_vec2 pos);
static void		_sample_pixel(t_vec2 pixel, t_canvas *canvas);


#define EDGE_THRESHOLD_MIN 0.0312
#define EDGE_THRESHOLD_MAX 0.0833

#define MAX 1
#define MIN 0

#define POS 0
#define NEG 1


/**
 * @brief Source: https://catlikecoding.com/unity/tutorials/custom-srp/fxaa/
 * 
 * @param canvas 
 */
void antialiasing(t_canvas *canvas)
{
	int	i, j;

	for (i = 1; i < canvas->width - 1; i++)
		for (j = 1; j < canvas->height - 1; j++)
			_sample_pixel((t_vec2) {i, j}, canvas);
}


void	find_luma_neighbours(t_luma_neighbour *neighbours, t_vec2 pix, mlx_image_t *img)
{
	neighbours->middle = rgb_to_luma(_get_pixel_color(img, pix));
	neighbours->left = rgb_to_luma(_get_pixel_color(img, (t_vec2) {pix.x - 1, pix.y}));
	neighbours->right = rgb_to_luma(_get_pixel_color(img, (t_vec2) {pix.x + 1, pix.y}));
	neighbours->up = rgb_to_luma(_get_pixel_color(img, (t_vec2) {pix.x, pix.y - 1}));
	neighbours->down = rgb_to_luma(_get_pixel_color(img, (t_vec2) {pix.x, pix.y + 1}));
	neighbours->left_up = rgb_to_luma(_get_pixel_color(img, (t_vec2) {pix.x - 1, pix.y - 1}));
	neighbours->right_up = rgb_to_luma(_get_pixel_color(img, (t_vec2) {pix.x + 1, pix.y - 1}));
	neighbours->left_down = rgb_to_luma(_get_pixel_color(img, (t_vec2) {pix.x - 1, pix.y + 1}));
	neighbours->right_down = rgb_to_luma(_get_pixel_color(img, (t_vec2) {pix.x + 1, pix.y + 1}));
}


bool	skip_fxaa(float luma_range, float luma_max)
{
	return (luma_range < fmax(EDGE_THRESHOLD_MIN, luma_max * EDGE_THRESHOLD_MAX));
}

void	find_luma_min_max(float luma[2], t_luma_neighbour *neighbours)
{
	luma[0] = fmin(neighbours->up, fmin(neighbours->down, fmin(neighbours->left, fmin(neighbours->right, fmin(neighbours->left_up, fmin(neighbours->right_up, fmin(neighbours->left_down, neighbours->right_down)))))));
	luma[1] = fmax(neighbours->up, fmax(neighbours->down, fmax(neighbours->left, fmax(neighbours->right, fmax(neighbours->left_up, fmax(neighbours->right_up, fmax(neighbours->left_down, neighbours->right_down)))))));
}

float saturate(float x)
{
	return fmax(0, fmax(1, x));
}

float smoothstep(float a, float b, float x)
{
	float	t;

	t = saturate((x - a)/(b - a));
	return t * t * (3.0 - (2.0 * t));
}

float	get_blend_factor(t_luma_neighbour *luma, float luma_range)
{
	float filter;
	
	filter = 2 * (luma->up + luma->right + luma->down + luma->left);
	filter += luma->left_up + luma->right_up + luma->left_down + luma->right_down;
	filter *= 1.0 / 12.0;
	filter = fabs(filter - luma->middle);
	filter = saturate(filter / luma_range);
	filter = smoothstep(0.0, 1.0, filter);
	return filter * filter;
}

bool is_horizontal_edge(t_luma_neighbour *luma)
{
	float horizontal =
		2.0 * fabs(luma->up + luma->down - 2.0 * luma->middle) +
		fabs(luma->right_up + luma->right_down - 2.0 * luma->right) +
		fabs(luma->left_up+ luma->left_down - 2.0 * luma->left);
	float vertical =
		2.0 * fabs(luma->right + luma->left - 2.0 * luma->middle) +
		fabs(luma->right_up + luma->left_up - 2.0 * luma->up) +
		fabs(luma->right_down + luma->left_down - 2.0 * luma->down);
	return horizontal >= vertical;
}


void	get_fxaa_edge(t_edge *edge, t_luma_neighbour *luma, t_vec2 *pix_pos)
{
	float lumaP, lumaN;
	float gradient_n, gradient_p;

	if (is_horizontal_edge(luma))
	{
		edge->horizontal = true;
		edge->pixel_step.x = 1;
		lumaP = luma->up;
		lumaN = luma->down;
	}
	else
	{
		edge->pixel_step.y = 1;
		lumaP = luma->left;
		lumaN = luma->right;
	}

	gradient_p = fabs(lumaP - luma->middle);
	gradient_n = fabs(lumaN - luma->middle);
	if (gradient_p < gradient_n)
	{
		vec2_scale(&edge->pixel_step, -1);
		edge->other_luma = lumaN;
		edge->luma = gradient_n;
	}
	else
	{
		edge->other_luma = lumaP;
		edge->luma = gradient_p;
	}
	edge->pixel_pos = *pix_pos;
	edge->init_pixel_pos = *pix_pos;
}

float	get_edge_blend_factor(
				t_luma_neighbour *luma,
				t_edge *initial_edge,
				t_canvas *canvas)
{
	t_edge edges[2];

	for (int i = 0; i < 2; i++)
	{
		edges[i] = *initial_edge;
		vec2_add_into(&edges[i].pixel_pos, &edges[i].pixel_step, &initial_edge->pixel_pos);
	}

	bool at_end_p = false;
	float edge_luma = 0.5 * (luma->middle + initial_edge->other_luma);
	float gradient_threshold = 0.25 * initial_edge->luma;

	if (initial_edge->horizontal)
	{
		edges[POS].pixel_step = (t_vec2) {0, 1};
		edges[NEG].pixel_step = (t_vec2) {0, -1};
	}
	else
	{
		edges[POS].pixel_step = (t_vec2) {1, 0};
		edges[NEG].pixel_step = (t_vec2) {-1, 0};
	}

	float luma_gradient_p, luma_gradient_n;
	for (int i = 0; i < 99 && !at_end_p; i++)
	{
		vec2_add(&edges[POS].init_pixel_pos, &edges[POS].pixel_step);
		vec2_add(&edges[POS].pixel_pos, &edges[POS].pixel_step);
		if (edges[POS].init_pixel_pos.x < 0 || edges[POS].init_pixel_pos.y < 0
			|| edges[POS].init_pixel_pos.x > canvas->width || edges[POS].init_pixel_pos.y > canvas->height)
			break;
		if (edges[POS].pixel_pos.x < 0 || edges[POS].pixel_pos.y < 0
			|| edges[POS].pixel_pos.x > canvas->width || edges[POS].pixel_pos.y > canvas->height)
			break;
		float luma = rgb_to_luma(_get_pixel_color(canvas->back, edges[POS].pixel_pos));
		float luma_compair = rgb_to_luma(_get_pixel_color(canvas->back, edges[POS].init_pixel_pos));
		luma = 0.5 * (luma + luma_compair);
		luma_gradient_p = luma - edge_luma;
		at_end_p = fabs(luma_gradient_p) >= gradient_threshold;
	}


	bool at_end_n = false;
	for (int i = 0; i < 99 && !at_end_n; i++)
	{
		vec2_add(&edges[NEG].init_pixel_pos, &edges[NEG].pixel_step);
		vec2_add(&edges[NEG].pixel_pos, &edges[NEG].pixel_step);
		if (edges[NEG].init_pixel_pos.x < 0 || edges[NEG].init_pixel_pos.y < 0
			|| edges[NEG].init_pixel_pos.x > canvas->width || edges[NEG].init_pixel_pos.y > canvas->height)
			break;
		if (edges[NEG].pixel_pos.x < 0 || edges[NEG].pixel_pos.y < 0
			|| edges[NEG].pixel_pos.x > canvas->width || edges[NEG].pixel_pos.y > canvas->height)
			break;
		float luma = rgb_to_luma(_get_pixel_color(canvas->back, edges[NEG].pixel_pos));
		float luma_compair = rgb_to_luma(_get_pixel_color(canvas->back, edges[NEG].init_pixel_pos));
		luma = 0.5 * (luma + luma_compair);
		luma_gradient_n = luma - edge_luma;
		at_end_n = fabs(luma_gradient_n) >= gradient_threshold;
	}
	float distance_to_end_p, distance_to_end_n;

	if (initial_edge->horizontal)
	{
		distance_to_end_p = fabs(edges[POS].pixel_pos.y - initial_edge->pixel_pos.y);
		distance_to_end_n = fabs(edges[NEG].pixel_pos.y - initial_edge->pixel_pos.y);
	}
	else
	{
		distance_to_end_p = fabs(edges[POS].pixel_pos.x - initial_edge->pixel_pos.x);
		distance_to_end_n = fabs(edges[NEG].pixel_pos.x - initial_edge->pixel_pos.x);
	}
	bool delta_sign;
	float distance_to_nearest_end;
	if (distance_to_end_p <= distance_to_end_n)
	{
		distance_to_nearest_end = distance_to_end_p;
		delta_sign = luma_gradient_p >= 0;
	}
	else
	{
		distance_to_nearest_end = distance_to_end_n;
		delta_sign = luma_gradient_n >= 0;
	}
	if (delta_sign == (luma->middle - edge_luma >= 0))
		return 0.0f;
	return (1.0 - (distance_to_nearest_end / (distance_to_end_n + distance_to_end_p)));
}

static void	_sample_pixel(t_vec2 pix, t_canvas *canvas)
{
	t_vec3				pixel_color_vec;
	t_luma_neighbour	luma;
	float				luma_min_max[2] = {0};
	float				luma_range;
	t_color				new_color= (t_color) {0};
	t_vec3				new_color_vec = (t_vec3) {0};
	t_edge				initial_edge = {0};


	pixel_color_vec = _get_pixel_color(canvas->back, pix);
	find_luma_neighbours(&luma, pix, canvas->back);
	find_luma_min_max(luma_min_max, &luma);
	luma_range = luma_min_max[MAX] - luma_min_max[MIN];
	new_color = (t_color) {pixel_color_vec.x, pixel_color_vec.y, pixel_color_vec.z, 0};
	if (skip_fxaa(luma_range, luma_min_max[MAX]))
	{
		mlx_put_pixel(canvas->scaled_img, pix.x, pix.y, color_to_int(&new_color));
		return;
	}
	else
	{
		float sub_pixel_blending = get_blend_factor(&luma, luma_range);
		get_fxaa_edge(&initial_edge, &luma, &pix);
		float edge_blend_factor = get_edge_blend_factor(&luma, &initial_edge, canvas);
		t_vec2 pixel_color_blend_pos;
		vec2_add_into(&pixel_color_blend_pos, &pix, &initial_edge.pixel_step);
		t_vec3 color_to_blend_with = _get_pixel_color(canvas->back, pixel_color_blend_pos);
		mix_color_into(
			&new_color_vec,
			&pixel_color_vec,
			&color_to_blend_with,
			fmax(sub_pixel_blending, edge_blend_factor));
		new_color = (t_color) {new_color_vec.x, new_color_vec.y, new_color_vec.z, 0};
		mlx_put_pixel(canvas->scaled_img, pix.x, pix.y, color_to_int(&new_color));
	}
}

static t_vec3	_get_pixel_color(mlx_image_t *img, t_vec2 pos)
{
	t_vec3	color;
	int		index;
	int		coords[2];

	coords[0] = pos.x;
	coords[1] = pos.y;
	index = (coords[1] * img->width + coords[0]) * sizeof(uint32_t);
	color.x = (float)img->pixels[index];
	color.y = (float)img->pixels[index + 1];
	color.z = (float)img->pixels[index + 2];
	return (color);
}
