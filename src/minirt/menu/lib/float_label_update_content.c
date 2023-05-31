/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   float_label_update_content.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdubois <tdubois@student.42angouleme.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 11:21:44 by tdubois           #+#    #+#             */
/*   Updated: 2023/05/31 13:51:32 by tdubois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt/menu/menu.h>

#include <MLX42/MLX42.h>
#include <libft/libft.h>
#include <stddef.h>

void	float_label_update_content(
			mlx_t *mlx,
			t_menu *menu,
			t_float_label *label)
{
	char	buf[100];
	size_t	len;

	if (label->img != NULL)
		mlx_delete_image(mlx, label->img);
	len = ft_strlcpy(buf, label->prefix, sizeof(buf));
	if (len < sizeof(buf))
		ft_sftoa(*label->f, buf + len, sizeof(buf) - len);
	label->img = mlx_put_string(mlx, buf, 
			menu->background->instances->x + label->x,
			label->y);
	mlx_set_instance_depth(label->img->instances, 4);
}
