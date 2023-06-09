/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   canvas_swap.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdubois <tdubois@student.42angouleme.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 13:43:16 by tdubois           #+#    #+#             */
/*   Updated: 2023/06/09 15:15:23 by tdubois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt/app/canvas/canvas.h"

#include <stdbool.h>

#include "libft/libft.h"

void	canvas_swap(
			t_canvas *canvas)
{
	canvas->back->enabled = true;
	canvas->front->enabled = false;
	ft_swap(&canvas->front, &canvas->back);
}
