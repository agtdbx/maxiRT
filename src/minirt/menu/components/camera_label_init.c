/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_label_init.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdubois <tdubois@student.42angouleme.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 15:47:13 by tdubois           #+#    #+#             */
/*   Updated: 2023/06/01 09:45:54 by tdubois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt/menu/menu.h>

#include <MLX42/MLX42.h>

static void	_camera_dir_label_init(
				mlx_t *mlx,
				t_menu *menu,
				t_scene const *scene);

static void	_camera_pos_label_init(
				mlx_t *mlx,
				t_menu *menu,
				t_scene const *scene);

void	camera_label_init(
			mlx_t *mlx,
			t_menu *menu,
			t_scene const *scene)
{
	menu->camera_label_title = mlx_put_string(mlx, "camera:", 0, 10);
	_camera_dir_label_init(mlx, menu, scene);
	_camera_pos_label_init(mlx, menu, scene);
}

static void	_camera_pos_label_init(
				mlx_t *mlx,
				t_menu *menu,
				t_scene const *scene)
{
	menu->camera_pos_label.title = "position:";
	menu->camera_pos_label.x = 20;
	menu->camera_pos_label.y = 40;
	menu->camera_pos_label.img_title = mlx_put_string(
				mlx, menu->camera_pos_label.title,
				menu->camera_pos_label.x + menu->background->instances->x,
				menu->camera_pos_label.y);
	mlx_set_instance_depth(menu->camera_pos_label.img_title->instances, 4);
	menu->camera_pos_label.label_x.prefix = "x: ";
	menu->camera_pos_label.label_x.x = menu->camera_pos_label.x;
	menu->camera_pos_label.label_x.y = menu->camera_pos_label.y + 20;
	menu->camera_pos_label.label_x.f = &scene->camera->pos.x;
	menu->camera_pos_label.label_x.img = NULL;
	menu->camera_pos_label.label_y.prefix = "y: ";
	menu->camera_pos_label.label_y.x = menu->camera_pos_label.x;
	menu->camera_pos_label.label_y.y = menu->camera_pos_label.y + 40;
	menu->camera_pos_label.label_y.f = &scene->camera->pos.y;
	menu->camera_pos_label.label_y.img = NULL;
	menu->camera_pos_label.label_z.prefix = "z: ";
	menu->camera_pos_label.label_z.x = menu->camera_pos_label.x;
	menu->camera_pos_label.label_z.y = menu->camera_pos_label.y + 60;
	menu->camera_pos_label.label_z.f = &scene->camera->pos.z;
	menu->camera_pos_label.label_z.img = NULL;
	vec3_label_draw(mlx, menu, &menu->camera_pos_label);
}

static void	_camera_dir_label_init(
				mlx_t *mlx,
				t_menu *menu,
				t_scene const *scene)
{
	menu->camera_dir_label.title = "direction:";
	menu->camera_dir_label.x = 200;
	menu->camera_dir_label.y = 40;
	menu->camera_dir_label.img_title = mlx_put_string(
				mlx, menu->camera_dir_label.title,
				menu->camera_dir_label.x + menu->background->instances->x,
				menu->camera_dir_label.y);
	mlx_set_instance_depth(menu->camera_dir_label.img_title->instances, 4);
	menu->camera_dir_label.label_x.prefix = "x: ";
	menu->camera_dir_label.label_x.x = menu->camera_dir_label.x;
	menu->camera_dir_label.label_x.y = menu->camera_dir_label.y + 20;
	menu->camera_dir_label.label_x.f = &scene->camera->direction.x;
	menu->camera_dir_label.label_x.img = NULL;
	menu->camera_dir_label.label_y.prefix = "y: ";
	menu->camera_dir_label.label_y.x = menu->camera_dir_label.x;
	menu->camera_dir_label.label_y.y = menu->camera_dir_label.y + 40;
	menu->camera_dir_label.label_y.f = &scene->camera->direction.y;
	menu->camera_dir_label.label_y.img = NULL;
	menu->camera_dir_label.label_z.prefix = "z: ";
	menu->camera_dir_label.label_z.x = menu->camera_dir_label.x;
	menu->camera_dir_label.label_z.y = menu->camera_dir_label.y + 60;
	menu->camera_dir_label.label_z.f = &scene->camera->direction.z;
	menu->camera_dir_label.label_z.img = NULL;
	vec3_label_draw(mlx, menu, &menu->camera_dir_label);
}
