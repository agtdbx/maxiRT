/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   int_label_draw.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdubois <tdubois@student.42angouleme.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 09:47:13 by tdubois           #+#    #+#             */
/*   Updated: 2023/06/01 09:54:43 by tdubois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt/menu/menu.h>

#include <MLX42/MLX42.h>
#include <libft/libft.h>
#include <stddef.h>

static void	_update_content(
				mlx_t *mlx,
				t_menu *menu,
				t_int_label *label);

static void	_update_position(
				t_menu *menu,
				t_int_label *label);

void	int_label_draw(
			mlx_t *mlx,
			t_menu *menu,
			t_int_label *label)
{
	_update_content(mlx, menu, label);
	_update_position(menu, label);
}

static void	_update_content(
				mlx_t *mlx,
				t_menu *menu,
				t_int_label *label)
{
	char	buf[100];
	size_t	len;

	if (label->img != NULL)
		mlx_delete_image(mlx, label->img);
	len = ft_strlcpy(buf, label->prefix, sizeof(buf));
	if (len < sizeof(buf))
		ft_sitoa(*label->i, buf + len, sizeof(buf) - len);
	label->img = mlx_put_string(mlx, buf, 
			menu->background->instances->x + label->x,
			label->y);
	mlx_set_instance_depth(label->img->instances, 4);
}

static void	_update_position(
				t_menu *menu,
				t_int_label *label)
{
	if (label->img == NULL)
		return ;
	label->img->instances->x = menu->background->instances->x + label->x;
	label->img->instances->y = menu->background->instances->y + label->y;
}
