/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perlin_noise.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gugus <gugus@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 12:52:20 by aderouba          #+#    #+#             */
/*   Updated: 2025/01/16 04:08:43 by gugus            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt/app/app.h"
#include "minirt/app/utils/geometry/geometry.h"

#include <time.h>
#include <stdlib.h>

#define PERLIN_NOISE_LIST_SIZE 32
#define PERLIN_NOISE_MASK 31
#define PERLIN_NOISE_SIZE 16

static void		generate_perlin_noise(
					int *perlin_noise);
static t_vec2	*get_constant_vector(
					int value);
static float	fade(
					float value);
static float	lerp(
					float start,
					float end,
					float ratio);


float	get_perlin_noise_value(
			float x,
			float y)
{
	static bool	perlin_noise_generated = false;
	static int	perlin_noise[PERLIN_NOISE_LIST_SIZE] = {0};
	int			pnX;
	int			pnY;
	float		x_ratio;
	float		y_ratio;
	t_vec2		vecLeftTop;
	t_vec2		vecRightTop;
	t_vec2		vecLeftBot;
	t_vec2		vecRightBot;
	float		valueLeftTop;
	float		valueRightTop;
	float		valueLeftBot;
	float		valueRightBot;
	float		dotLeftTop;
	float		dotRightTop;
	float		dotLeftBot;
	float		dotRightBot;
	float		topValue;
	float		botValue;

	if (!perlin_noise_generated)
	{
		generate_perlin_noise(perlin_noise);
		perlin_noise_generated = true;
	}

	x *= PERLIN_NOISE_SIZE;
	y *= PERLIN_NOISE_SIZE;

	pnX = ((int)x) & PERLIN_NOISE_MASK;
	pnY = ((int)y) & PERLIN_NOISE_MASK;

	x_ratio = x - ((int)x);
	y_ratio = y - ((int)y);

	vecLeftTop = (t_vec2){x_ratio, y_ratio - 1.0f};
	vecRightTop = (t_vec2){x_ratio - 1.0f, y_ratio - 1.0f};
	vecLeftBot = (t_vec2){x_ratio, y_ratio};
	vecRightBot = (t_vec2){x_ratio - 1.0f, y_ratio};

	valueLeftTop = perlin_noise[perlin_noise[pnX] + pnY + 1];
	valueRightTop = perlin_noise[perlin_noise[pnX + 1] + pnY + 1];
	valueLeftBot = perlin_noise[perlin_noise[pnX] + pnY];
	valueRightBot = perlin_noise[perlin_noise[pnX + 1] + pnY];

	dotLeftTop = vec2_dot(&vecLeftTop, get_constant_vector(valueLeftTop));
	dotRightTop = vec2_dot(&vecRightTop, get_constant_vector(valueRightTop));
	dotLeftBot = vec2_dot(&vecLeftBot, get_constant_vector(valueLeftBot));
	dotRightBot = vec2_dot(&vecRightBot, get_constant_vector(valueRightBot));

	x_ratio = fade(x_ratio);
	y_ratio = fade(y_ratio);

	topValue = lerp(dotLeftTop, dotRightTop, x_ratio);
	botValue = lerp(dotLeftBot, dotRightBot, x_ratio);

	return (lerp(botValue, topValue, y_ratio));
}

static void	generate_perlin_noise(
				int *perlin_noise)
{
	int	shuffleIndex, tmp;

	srand(time(NULL));
	for (int i = 0; i < PERLIN_NOISE_SIZE; i++)
		perlin_noise[i] = i;

	for (int i = 0; i < PERLIN_NOISE_SIZE; i++)
	{
		shuffleIndex = rand() % PERLIN_NOISE_SIZE;
		tmp = perlin_noise[i];
		perlin_noise[i] = perlin_noise[shuffleIndex];
		perlin_noise[shuffleIndex] = tmp;
	}

	for (int i = 0; i < PERLIN_NOISE_SIZE; i++)
		perlin_noise[i + PERLIN_NOISE_SIZE] = perlin_noise[i];
}

static t_vec2	*get_constant_vector(
					int value)
{
	static	t_vec2	vecLeftTop = (t_vec2){1.0, 1.0};
	static	t_vec2	vecRightTop = (t_vec2){-1.0, 1.0};
	static	t_vec2	vecRightBot = (t_vec2){-1.0, -1.0};
	static	t_vec2	vecLeftBot = (t_vec2){1.0, -1.0};
	int				height;

	height = value & 3;
	if (height == 0)
		return (&vecLeftTop);
	else if (height == 1)
		return (&vecRightTop);
	else if (height == 2)
		return (&vecRightBot);
	return (&vecLeftBot);
}

static float	fade(
					float value)
{
	return (((6 * value -  15) *  value + 10) *  value * value * value);
}

static float	lerp(
					float start,
					float end,
					float ratio)
{
	return (start + (end - start) * ratio);
}
