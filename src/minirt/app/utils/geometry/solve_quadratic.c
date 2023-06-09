/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve_quadratic.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdubois <tdubois@student.42angouleme.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 17:29:33 by tdubois           #+#    #+#             */
/*   Updated: 2023/06/09 15:04:02 by tdubois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt/app/utils/geometry/geometry.h"

#include <math.h>
#include <stdbool.h>

//TODO(tdubois): should be removed

/**
 * Solve quadratic equation (E) a*X^2 + bX + c = 0
 * @param[in] a
 * @param[in] b
 * @param[in] c
 * @returns Wether equation has a real solution
 */
extern inline bool	solve_quadratic(
						float a,
						float b,
						float c,
						float solutions[2])
{
	float const	discriminant = (b * b) - (4.0f * a * c);
	float		srqt_discriminant;
	float		denom;

	if (discriminant < 0)
		return (false);
	srqt_discriminant = sqrtf(discriminant);
	denom = 0.5f / a;
	solutions[0] = (-b - srqt_discriminant) * denom;
	solutions[1] = (-b + srqt_discriminant) * denom;
	return (true);
}
