/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   canvas_swap.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdubois <tdubois@student.42angouleme.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 13:43:16 by tdubois           #+#    #+#             */
/*   Updated: 2023/05/04 13:50:08 by tdubois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt/canvas/canvas.h>

#include <libft/libft.h>

void	canvas_swap(
			t_canvas *canvas)
{
	canvas->back->enabled = true;
	canvas->front->enabled = false;
	ft_swap(&canvas->front, &canvas->back);
}
