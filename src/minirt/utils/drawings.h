/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawings.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdubois <tdubois@student.42angouleme.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 20:01:33 by tdubois           #+#    #+#             */
/*   Updated: 2023/05/31 20:55:47 by tdubois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DRAWINGS_H
# define DRAWINGS_H

# include <MLX42/MLX42.h>
# include <stdint.h>

void	img_fill(
			mlx_image_t *img,
			int32_t color);

void	img_fill_square(
			mlx_image_t *img,
			int32_t coords[2],
			int32_t size,
			int32_t color);

#endif // DRAWINGS_H
