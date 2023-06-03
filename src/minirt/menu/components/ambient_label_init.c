/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ambient_label_init.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdubois <tdubois@student.42angouleme.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 08:35:33 by tdubois           #+#    #+#             */
/*   Updated: 2023/06/03 00:41:40 by tdubois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt/menu/menu.h>

#include <MLX42/MLX42.h>

static void	_ambient_color_label_init(
				mlx_t *mlx,
				t_menu *menu,
				t_scene const *scene);

static void	_ambient_ratio_label_init(
				t_menu *menu,
				t_scene const *scene);

void	ambient_label_init(
			mlx_t *mlx,
			t_menu *menu,
			t_scene const *scene)
{
	menu->ambient_label_title = mlx_put_string(mlx, "ambient light:", 0, 150);
	_ambient_color_label_init(mlx, menu, scene);
	_ambient_ratio_label_init(menu, scene);
}

static void	_ambient_color_label_init(
				mlx_t *mlx,
				t_menu *menu,
				t_scene const *scene)
{
	menu->ambient_color_label.title = "color:";
	menu->ambient_color_label.x = 20;
	menu->ambient_color_label.y = 180;
	menu->ambient_color_label.img_title = mlx_put_string(
				mlx, menu->ambient_color_label.title,
				menu->ambient_color_label.x + menu->background->instances->x,
				menu->ambient_color_label.y);
	menu->ambient_color_label.label_r.prefix = "r: ";
	menu->ambient_color_label.label_r.x = menu->ambient_color_label.x;
	menu->ambient_color_label.label_r.y = menu->ambient_color_label.y + 20;
	menu->ambient_color_label.label_r.f = &scene->ambient_lightning->color.r;
	menu->ambient_color_label.label_r.img = NULL;
	menu->ambient_color_label.label_g.prefix = "g: ";
	menu->ambient_color_label.label_g.x = menu->ambient_color_label.x;
	menu->ambient_color_label.label_g.y = menu->ambient_color_label.y + 40;
	menu->ambient_color_label.label_g.f = &scene->ambient_lightning->color.g;
	menu->ambient_color_label.label_g.img = NULL;
	menu->ambient_color_label.label_b.prefix = "b: ";
	menu->ambient_color_label.label_b.x = menu->ambient_color_label.x;
	menu->ambient_color_label.label_b.y = menu->ambient_color_label.y + 60;
	menu->ambient_color_label.label_b.f = &scene->ambient_lightning->color.b;
	menu->ambient_color_label.label_b.img = NULL;
	color_label_draw(mlx, menu, &menu->ambient_color_label);
}

static void	_ambient_ratio_label_init(
				t_menu *menu,
				t_scene const *scene)
{
	t_float_label *const	label = &menu->ambient_ratio_label;

	label->prefix = "ratio: ";
	label->x = 200;
	label->y = 180;
	label->f = &scene->ambient_lightning->brightness;
	label->img = NULL;
}
