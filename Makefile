# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: auguste <auguste@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/31 15:41:02 by tdubois           #+#    #+#              #
#    Updated: 2024/04/21 12:32:08 by auguste          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%#
#%%%% CONFIGURATION %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%#

MAKEFLAGS	+=	--no-print-directory

.POSIX:
.SILENT:
.DELETE_ON_ERROR:
.SECONDEXPANSION:

#==============================================================================#
#==== GOALS ===================================================================#

NAME		:=	maxiRT

LIBMLX42	:=	lib/mlx42/build/libmlx42.a
LIBFT		:=	lib/libft/libft.a

#==============================================================================#
#==== DIRECTORIES =============================================================#

BUILD_BONUS	:= .build_bonus
ifdef BONUS
SRC			:=	src_bonus
SRCS		:=	src_bonus/minirt/app/app_loop_bonus.c \
				src_bonus/minirt/app/app_start_bonus.c \
				src_bonus/minirt/app/canvas/canvas_init_bonus.c \
				src_bonus/minirt/app/canvas/canvas_swap_bonus.c \
				src_bonus/minirt/app/input_handlers/handle_menu_toggling_bonus.c \
				src_bonus/minirt/app/input_handlers/handle_mouse_clicks_bonus.c \
				src_bonus/minirt/app/input_handlers/handle_rotations_bonus.c \
				src_bonus/minirt/app/input_handlers/handle_translations_bonus.c \
				src_bonus/minirt/app/input_handlers/handle_window_resizing_bonus.c \
				src_bonus/minirt/app/menu/components/ambient/ambient_label_draw_bonus.c \
				src_bonus/minirt/app/menu/components/ambient/ambient_label_hide_bonus.c \
				src_bonus/minirt/app/menu/components/ambient/ambient_label_init_bonus.c \
				src_bonus/minirt/app/menu/components/ambient/ambient_label_show_bonus.c \
				src_bonus/minirt/app/menu/components/background_draw_bonus.c \
				src_bonus/minirt/app/menu/components/camera/camera_label_draw_bonus.c \
				src_bonus/minirt/app/menu/components/camera/camera_label_hide_bonus.c \
				src_bonus/minirt/app/menu/components/camera/camera_label_init_bonus.c \
				src_bonus/minirt/app/menu/components/camera/camera_label_show_bonus.c \
				src_bonus/minirt/app/menu/components/cone/cone_panel_draw_bonus.c \
				src_bonus/minirt/app/menu/components/cone/cone_panel_hide_bonus.c \
				src_bonus/minirt/app/menu/components/cone/cone_panel_init_bonus.c \
				src_bonus/minirt/app/menu/components/cone/cone_panel_register_bonus.c \
				src_bonus/minirt/app/menu/components/cone/cone_panel_show_bonus.c \
				src_bonus/minirt/app/menu/components/cube/cube_panel_draw_bonus.c \
				src_bonus/minirt/app/menu/components/cube/cube_panel_hide_bonus.c \
				src_bonus/minirt/app/menu/components/cube/cube_panel_init_bonus.c \
				src_bonus/minirt/app/menu/components/cube/cube_panel_register_bonus.c \
				src_bonus/minirt/app/menu/components/cube/cube_panel_show_bonus.c \
				src_bonus/minirt/app/menu/components/cylinder/cylinder_panel_draw_bonus.c \
				src_bonus/minirt/app/menu/components/cylinder/cylinder_panel_hide_bonus.c \
				src_bonus/minirt/app/menu/components/cylinder/cylinder_panel_init_bonus.c \
				src_bonus/minirt/app/menu/components/cylinder/cylinder_panel_register_bonus.c \
				src_bonus/minirt/app/menu/components/cylinder/cylinder_panel_show_bonus.c \
				src_bonus/minirt/app/menu/components/init_labels_bonus.c \
				src_bonus/minirt/app/menu/components/light/light_panel_draw_bonus.c \
				src_bonus/minirt/app/menu/components/light/light_panel_hide_bonus.c \
				src_bonus/minirt/app/menu/components/light/light_panel_init_bonus.c \
				src_bonus/minirt/app/menu/components/light/light_panel_register_bonus.c \
				src_bonus/minirt/app/menu/components/light/light_panel_show_bonus.c \
				src_bonus/minirt/app/menu/components/object/object_panel_draw_bonus.c \
				src_bonus/minirt/app/menu/components/object/object_panel_hide_bonus.c \
				src_bonus/minirt/app/menu/components/object/object_panel_init_bonus.c \
				src_bonus/minirt/app/menu/components/object/object_panel_register_bonus.c \
				src_bonus/minirt/app/menu/components/object/object_panel_show_bonus.c \
				src_bonus/minirt/app/menu/components/object_file/object_file_panel_draw_bonus.c \
				src_bonus/minirt/app/menu/components/object_file/object_file_panel_hide_bonus.c \
				src_bonus/minirt/app/menu/components/object_file/object_file_panel_init_bonus.c \
				src_bonus/minirt/app/menu/components/object_file/object_file_panel_register_bonus.c \
				src_bonus/minirt/app/menu/components/object_file/object_file_panel_show_bonus.c \
				src_bonus/minirt/app/menu/components/plane/plane_panel_draw_bonus.c \
				src_bonus/minirt/app/menu/components/plane/plane_panel_hide_bonus.c \
				src_bonus/minirt/app/menu/components/plane/plane_panel_init_bonus.c \
				src_bonus/minirt/app/menu/components/plane/plane_panel_register_bonus.c \
				src_bonus/minirt/app/menu/components/plane/plane_panel_show_bonus.c \
				src_bonus/minirt/app/menu/components/sphere/sphere_panel_draw_bonus.c \
				src_bonus/minirt/app/menu/components/sphere/sphere_panel_hide_bonus.c \
				src_bonus/minirt/app/menu/components/sphere/sphere_panel_init_bonus.c \
				src_bonus/minirt/app/menu/components/sphere/sphere_panel_register_bonus.c \
				src_bonus/minirt/app/menu/components/sphere/sphere_panel_show_bonus.c \
				src_bonus/minirt/app/menu/components/triangle/triangle_panel_draw_bonus.c \
				src_bonus/minirt/app/menu/components/triangle/triangle_panel_hide_bonus.c \
				src_bonus/minirt/app/menu/components/triangle/triangle_panel_init_bonus.c \
				src_bonus/minirt/app/menu/components/triangle/triangle_panel_register_bonus.c \
				src_bonus/minirt/app/menu/components/triangle/triangle_panel_show_bonus.c \
				src_bonus/minirt/app/menu/lib/button/button_draw_bonus.c \
				src_bonus/minirt/app/menu/lib/button/button_hide_bonus.c \
				src_bonus/minirt/app/menu/lib/button/button_init_bonus.c \
				src_bonus/minirt/app/menu/lib/button/button_show_bonus.c \
				src_bonus/minirt/app/menu/lib/color_label/color_label_draw_bonus.c \
				src_bonus/minirt/app/menu/lib/color_label/color_label_hide_bonus.c \
				src_bonus/minirt/app/menu/lib/color_label/color_label_init_bonus.c \
				src_bonus/minirt/app/menu/lib/color_label/color_label_show_bonus.c \
				src_bonus/minirt/app/menu/lib/float_label/float_label_draw_bonus.c \
				src_bonus/minirt/app/menu/lib/float_label/float_label_hide_bonus.c \
				src_bonus/minirt/app/menu/lib/float_label/float_label_init_bonus.c \
				src_bonus/minirt/app/menu/lib/float_label/float_label_show_bonus.c \
				src_bonus/minirt/app/menu/lib/int_label/int_label_draw_bonus.c \
				src_bonus/minirt/app/menu/lib/int_label/int_label_hide_bonus.c \
				src_bonus/minirt/app/menu/lib/int_label/int_label_init_bonus.c \
				src_bonus/minirt/app/menu/lib/int_label/int_label_show_bonus.c \
				src_bonus/minirt/app/menu/lib/vec3_label/vec3_label_draw_bonus.c \
				src_bonus/minirt/app/menu/lib/vec3_label/vec3_label_hide_bonus.c \
				src_bonus/minirt/app/menu/lib/vec3_label/vec3_label_init_bonus.c \
				src_bonus/minirt/app/menu/lib/vec3_label/vec3_label_show_bonus.c \
				src_bonus/minirt/app/menu/menu_draw_bonus.c \
				src_bonus/minirt/app/menu/menu_hide_bonus.c \
				src_bonus/minirt/app/menu/menu_init_bonus.c \
				src_bonus/minirt/app/menu/menu_show_bonus.c \
				src_bonus/minirt/app/menu/menu_update_position_bonus.c \
				src_bonus/minirt/app/render/create_ray_from_pixel_coords_bonus.c \
				src_bonus/minirt/app/render/illumination/compute_illumination_bonus.c \
				src_bonus/minirt/app/render/intersections/bounding_box/test_intersection_with_bounding_box_bonus.c \
				src_bonus/minirt/app/render/intersections/compute_intersection_distance_bonus.c \
				src_bonus/minirt/app/render/intersections/compute_intersection_distance_from_inside_bonus.c \
				src_bonus/minirt/app/render/intersections/cone/test_intersection_with_cone_bonus.c \
				src_bonus/minirt/app/render/intersections/cone/test_intersection_with_cone_from_inside_bonus.c \
				src_bonus/minirt/app/render/intersections/cube/intersection_inside_x_bonus.c \
				src_bonus/minirt/app/render/intersections/cube/intersection_inside_y_bonus.c \
				src_bonus/minirt/app/render/intersections/cube/intersection_inside_z_bonus.c \
				src_bonus/minirt/app/render/intersections/cube/intersection_x_bonus.c \
				src_bonus/minirt/app/render/intersections/cube/intersection_y_bonus.c \
				src_bonus/minirt/app/render/intersections/cube/intersection_z_bonus.c \
				src_bonus/minirt/app/render/intersections/cube/test_intersection_with_cube_bonus.c \
				src_bonus/minirt/app/render/intersections/cube/test_intersection_with_cube_from_inside_bonus.c \
				src_bonus/minirt/app/render/intersections/cylinder/test_intersection_with_cylinder_bonus.c \
				src_bonus/minirt/app/render/intersections/cylinder/test_intersection_with_cylinder_from_inside_bonus.c \
				src_bonus/minirt/app/render/intersections/fetch_closer_spotlight_bonus.c \
				src_bonus/minirt/app/render/intersections/fetch_closest_intersections_bonus.c \
				src_bonus/minirt/app/render/intersections/intersect_loop_without_param_obj_bonus.c \
				src_bonus/minirt/app/render/intersections/object_file/test_intersection_with_object_file_bonus.c \
				src_bonus/minirt/app/render/intersections/object_file/test_intersection_with_object_file_from_inside_bonus.c \
				src_bonus/minirt/app/render/intersections/object_file/test_intersection_with_object_rectangle_bonus.c \
				src_bonus/minirt/app/render/intersections/object_file/test_intersection_with_object_triangle_bonus.c \
				src_bonus/minirt/app/render/intersections/plane/test_intersection_with_plane_bonus.c \
				src_bonus/minirt/app/render/intersections/sphere/test_intersection_with_sphere_bonus.c \
				src_bonus/minirt/app/render/intersections/sphere/test_intersection_with_sphere_from_inside_bonus.c \
				src_bonus/minirt/app/render/intersections/test_intersection_with_obj_bonus.c \
				src_bonus/minirt/app/render/intersections/triangle/test_intersection_with_triangle_bonus.c \
				src_bonus/minirt/app/render/mapping/color/apply_texture_bonus.c \
				src_bonus/minirt/app/render/mapping/color/get_base_color_object_bonus.c \
				src_bonus/minirt/app/render/mapping/normal_map/apply_normal_map_bonus.c \
				src_bonus/minirt/app/render/mapping/normal_map/compute_normal_base_cone_bonus.c \
				src_bonus/minirt/app/render/mapping/normal_map/compute_normal_base_cube_bonus.c \
				src_bonus/minirt/app/render/mapping/normal_map/compute_normal_base_cylinder_bonus.c \
				src_bonus/minirt/app/render/mapping/normal_map/compute_normal_base_object_file_bonus.c \
				src_bonus/minirt/app/render/mapping/normal_map/compute_normal_base_plane_bonus.c \
				src_bonus/minirt/app/render/mapping/normal_map/compute_normal_base_sphere_bonus.c \
				src_bonus/minirt/app/render/mapping/normal_map/compute_normal_base_triangle_bonus.c \
				src_bonus/minirt/app/render/mapping/normal_map/compute_normal_map_bonus.c \
				src_bonus/minirt/app/render/mapping/pixel_pos/get_cone_pixel_pos_bonus.c \
				src_bonus/minirt/app/render/mapping/pixel_pos/get_cube_pixel_pos_bonus.c \
				src_bonus/minirt/app/render/mapping/pixel_pos/get_cylinder_pixel_pos_bonus.c \
				src_bonus/minirt/app/render/mapping/pixel_pos/get_object_file_pixel_pos_bonus.c \
				src_bonus/minirt/app/render/mapping/pixel_pos/get_object_pixel_pos_bonus.c \
				src_bonus/minirt/app/render/mapping/pixel_pos/get_plane_pixel_pos_bonus.c \
				src_bonus/minirt/app/render/mapping/pixel_pos/get_sphere_pixel_pos_bonus.c \
				src_bonus/minirt/app/render/mapping/pixel_pos/get_triangle_pixel_pos_bonus.c \
				src_bonus/minirt/app/render/normal_rays/compute_normal_ray_bonus.c \
				src_bonus/minirt/app/render/normal_rays/compute_normal_ray_on_cone_bonus.c \
				src_bonus/minirt/app/render/normal_rays/compute_normal_ray_on_cube_bonus.c \
				src_bonus/minirt/app/render/normal_rays/compute_normal_ray_on_cylinder_bonus.c \
				src_bonus/minirt/app/render/normal_rays/compute_normal_ray_on_object_file_bonus.c \
				src_bonus/minirt/app/render/normal_rays/compute_normal_ray_on_plane_bonus.c \
				src_bonus/minirt/app/render/normal_rays/compute_normal_ray_on_sphere_bonus.c \
				src_bonus/minirt/app/render/normal_rays/compute_normal_ray_on_triangle_bonus.c \
				src_bonus/minirt/app/render/reflection/reflection_bonus.c \
				src_bonus/minirt/app/render/render_canvas_bonus.c \
				src_bonus/minirt/app/render/render_fast_on_front_canvas_bonus.c \
				src_bonus/minirt/app/render/render_next_pixels_til_tmax_on_back_canvas_bonus.c \
				src_bonus/minirt/app/render/render_ray_from_camera_bonus.c \
				src_bonus/minirt/app/render/render_ray_on_object_bonus.c \
				src_bonus/minirt/app/render/transparency/compute_refracted_color_bonus.c \
				src_bonus/minirt/app/scene/object_file_compute_constants/compute_object_bounding_box_bonus.c \
				src_bonus/minirt/app/scene/object_file_compute_constants/compute_object_rectangle_bonus.c \
				src_bonus/minirt/app/scene/object_file_compute_constants/compute_object_triangle_bonus.c \
				src_bonus/minirt/app/scene/object_file_compute_constants/object_binary_tree_bonus.c \
				src_bonus/minirt/app/scene/object_file_compute_constants/object_file_compute_constants_bonus.c \
				src_bonus/minirt/app/scene/camera_compute_constants_bonus.c \
				src_bonus/minirt/app/scene/compute_bounding_box_constants_bonus.c \
				src_bonus/minirt/app/scene/cone_compute_constants_bonus.c \
				src_bonus/minirt/app/scene/cube_compute_constants_bonus.c \
				src_bonus/minirt/app/scene/cylinder_compute_constants_bonus.c \
				src_bonus/minirt/app/scene/plane_compute_constants_bonus.c \
				src_bonus/minirt/app/scene/scene_add_object_bonus.c \
				src_bonus/minirt/app/scene/scene_del_bonus.c \
				src_bonus/minirt/app/scene/sphere_compute_constants_bonus.c \
				src_bonus/minirt/app/scene/triangle_compute_constants_bonus.c \
				src_bonus/minirt/app/utils/color/color_scale_bonus.c \
				src_bonus/minirt/app/utils/color/color_to_int_bonus.c \
				src_bonus/minirt/app/utils/drawings/img_draw_divider_bonus.c \
				src_bonus/minirt/app/utils/drawings/img_draw_square_bonus.c \
				src_bonus/minirt/app/utils/drawings/img_fill_bonus.c \
				src_bonus/minirt/app/utils/geometry/mat_product_bonus.c \
				src_bonus/minirt/app/utils/geometry/vec3_add_bonus.c \
				src_bonus/minirt/app/utils/geometry/vec3_add_into_bonus.c \
				src_bonus/minirt/app/utils/geometry/vec3_bonus.c \
				src_bonus/minirt/app/utils/geometry/vec3_cross_bonus.c \
				src_bonus/minirt/app/utils/geometry/vec3_dot_bonus.c \
				src_bonus/minirt/app/utils/geometry/vec3_dot_xyz_bonus.c \
				src_bonus/minirt/app/utils/geometry/vec3_linear_transform_bonus.c \
				src_bonus/minirt/app/utils/geometry/vec3_normalize_bonus.c \
				src_bonus/minirt/app/utils/geometry/vec3_normalize_into_bonus.c \
				src_bonus/minirt/app/utils/geometry/vec3_norm_bonus.c \
				src_bonus/minirt/app/utils/geometry/vec3_scale_bonus.c \
				src_bonus/minirt/app/utils/geometry/vec3_scale_into_bonus.c \
				src_bonus/minirt/app/utils/geometry/vec3_substract_bonus.c \
				src_bonus/minirt/app/utils/geometry/vec3_substract_into_bonus.c \
				src_bonus/minirt/app/utils/space_partition/is_bounding_box_inside_bounding_box_bonus.c \
				src_bonus/minirt/app/utils/space_partition/is_polygon_inside_object_bounding_box_bonus.c \
				src_bonus/minirt/app/utils/space_partition/set_min_max_bonus.c \
				src_bonus/minirt_bonus.c \
				src_bonus/minirt/parser/directives/parse_ambient_light_bonus.c \
				src_bonus/minirt/parser/directives/parse_camera_bonus.c \
				src_bonus/minirt/parser/directives/parse_comment_bonus.c \
				src_bonus/minirt/parser/directives/parse_cone_bonus.c \
				src_bonus/minirt/parser/directives/parse_cube_bonus.c \
				src_bonus/minirt/parser/directives/parse_cylinder_bonus.c \
				src_bonus/minirt/parser/directives/parse_object_file_bonus.c \
				src_bonus/minirt/parser/directives/parse_plane_bonus.c \
				src_bonus/minirt/parser/directives/parse_sphere_bonus.c \
				src_bonus/minirt/parser/directives/parse_spotlight_bonus.c \
				src_bonus/minirt/parser/directives/parse_triangle_bonus.c \
				src_bonus/minirt/parser/dot_obj_file/apply_parsing_to_object_file_bonus.c \
				src_bonus/minirt/parser/dot_obj_file/parse_dot_file_bonus.c \
				src_bonus/minirt/parser/dot_obj_file/parse_dot_struct_bonus.c \
				src_bonus/minirt/parser/error_logs/put_directive_error_bonus.c \
				src_bonus/minirt/parser/error_logs/put_field_error_bonus.c \
				src_bonus/minirt/parser/error_logs/put_unknown_directive_error_bonus.c \
				src_bonus/minirt/parser/fast_get_next_line/fast_get_next_line_bonus.c \
				src_bonus/minirt/parser/fast_get_next_line/fast_get_next_line_utils_bonus.c \
				src_bonus/minirt/parser/fields/parse_brightness_bonus.c \
				src_bonus/minirt/parser/fields/parse_color_bonus.c \
				src_bonus/minirt/parser/fields/parse_diameter_bonus.c \
				src_bonus/minirt/parser/fields/parse_direction_bonus.c \
				src_bonus/minirt/parser/fields/parse_dot_obj_file_bonus.c \
				src_bonus/minirt/parser/fields/parse_float_bonus.c \
				src_bonus/minirt/parser/fields/parse_fov_bonus.c \
				src_bonus/minirt/parser/fields/parse_png_bonus.c \
				src_bonus/minirt/parser/fields/parse_vec3_bonus.c \
				src_bonus/minirt/parser/parse_directive_bonus.c \
				src_bonus/minirt/parser/parse_field_bonus.c \
				src_bonus/minirt/parser/parse_file_bonus.c \
				src_bonus/minirt/parser/parse_lines_bonus.c
BUILD		:=	.build_bonus
else
SRC			:=	src
SRCS		:=	src/minirt/app/app_loop.c \
				src/minirt/app/app_start.c \
				src/minirt/app/canvas/canvas_init.c \
				src/minirt/app/canvas/canvas_swap.c \
				src/minirt/app/input_handlers/handle_menu_toggling.c \
				src/minirt/app/input_handlers/handle_mouse_clicks.c \
				src/minirt/app/input_handlers/handle_rotations.c \
				src/minirt/app/input_handlers/handle_translations.c \
				src/minirt/app/input_handlers/handle_window_resizing.c \
				src/minirt/app/menu/components/ambient/ambient_label_draw.c \
				src/minirt/app/menu/components/ambient/ambient_label_hide.c \
				src/minirt/app/menu/components/ambient/ambient_label_init.c \
				src/minirt/app/menu/components/ambient/ambient_label_show.c \
				src/minirt/app/menu/components/background_draw.c \
				src/minirt/app/menu/components/camera/camera_label_draw.c \
				src/minirt/app/menu/components/camera/camera_label_hide.c \
				src/minirt/app/menu/components/camera/camera_label_init.c \
				src/minirt/app/menu/components/camera/camera_label_show.c \
				src/minirt/app/menu/components/cylinder/cylinder_panel_draw.c \
				src/minirt/app/menu/components/cylinder/cylinder_panel_hide.c \
				src/minirt/app/menu/components/cylinder/cylinder_panel_init.c \
				src/minirt/app/menu/components/cylinder/cylinder_panel_register.c \
				src/minirt/app/menu/components/cylinder/cylinder_panel_show.c \
				src/minirt/app/menu/components/init_labels.c \
				src/minirt/app/menu/components/light/light_panel_draw.c \
				src/minirt/app/menu/components/light/light_panel_hide.c \
				src/minirt/app/menu/components/light/light_panel_init.c \
				src/minirt/app/menu/components/light/light_panel_register.c \
				src/minirt/app/menu/components/light/light_panel_show.c \
				src/minirt/app/menu/components/object/object_panel_draw.c \
				src/minirt/app/menu/components/object/object_panel_hide.c \
				src/minirt/app/menu/components/object/object_panel_init.c \
				src/minirt/app/menu/components/object/object_panel_register.c \
				src/minirt/app/menu/components/object/object_panel_show.c \
				src/minirt/app/menu/components/plane/plane_panel_draw.c \
				src/minirt/app/menu/components/plane/plane_panel_hide.c \
				src/minirt/app/menu/components/plane/plane_panel_init.c \
				src/minirt/app/menu/components/plane/plane_panel_register.c \
				src/minirt/app/menu/components/plane/plane_panel_show.c \
				src/minirt/app/menu/components/sphere/sphere_panel_draw.c \
				src/minirt/app/menu/components/sphere/sphere_panel_hide.c \
				src/minirt/app/menu/components/sphere/sphere_panel_init.c \
				src/minirt/app/menu/components/sphere/sphere_panel_register.c \
				src/minirt/app/menu/components/sphere/sphere_panel_show.c \
				src/minirt/app/menu/lib/button/button_draw.c \
				src/minirt/app/menu/lib/button/button_hide.c \
				src/minirt/app/menu/lib/button/button_init.c \
				src/minirt/app/menu/lib/button/button_show.c \
				src/minirt/app/menu/lib/color_label/color_label_draw.c \
				src/minirt/app/menu/lib/color_label/color_label_hide.c \
				src/minirt/app/menu/lib/color_label/color_label_init.c \
				src/minirt/app/menu/lib/color_label/color_label_show.c \
				src/minirt/app/menu/lib/float_label/float_label_draw.c \
				src/minirt/app/menu/lib/float_label/float_label_hide.c \
				src/minirt/app/menu/lib/float_label/float_label_init.c \
				src/minirt/app/menu/lib/float_label/float_label_show.c \
				src/minirt/app/menu/lib/int_label/int_label_draw.c \
				src/minirt/app/menu/lib/int_label/int_label_hide.c \
				src/minirt/app/menu/lib/int_label/int_label_init.c \
				src/minirt/app/menu/lib/int_label/int_label_show.c \
				src/minirt/app/menu/lib/vec_label/vec3_label_draw.c \
				src/minirt/app/menu/lib/vec_label/vec3_label_hide.c \
				src/minirt/app/menu/lib/vec_label/vec3_label_init.c \
				src/minirt/app/menu/lib/vec_label/vec3_label_show.c \
				src/minirt/app/menu/menu_draw.c \
				src/minirt/app/menu/menu_hide.c \
				src/minirt/app/menu/menu_init.c \
				src/minirt/app/menu/menu_show.c \
				src/minirt/app/menu/menu_update_position.c \
				src/minirt/app/render/create_ray_from_pixel_coords.c \
				src/minirt/app/render/illumination/compute_illumination.c \
				src/minirt/app/render/intersections/compute_intersection_distance.c \
				src/minirt/app/render/intersections/compute_intersection_distance_from_inside.c \
				src/minirt/app/render/intersections/cylinder/test_intersection_with_cylinder.c \
				src/minirt/app/render/intersections/cylinder/test_intersection_with_cylinder_from_inside.c \
				src/minirt/app/render/intersections/fetch_closer_spotlight.c \
				src/minirt/app/render/intersections/fetch_closest_intersections.c \
				src/minirt/app/render/intersections/intersect_loop_without_param_obj.c \
				src/minirt/app/render/intersections/plane/test_intersection_with_plane.c \
				src/minirt/app/render/intersections/sphere/test_intersection_with_sphere.c \
				src/minirt/app/render/intersections/sphere/test_intersection_with_sphere_from_inside.c \
				src/minirt/app/render/intersections/test_intersection_with_obj.c \
				src/minirt/app/render/normal_rays/compute_normal_ray.c \
				src/minirt/app/render/normal_rays/compute_normal_ray_on_cylinder.c \
				src/minirt/app/render/normal_rays/compute_normal_ray_on_plane.c \
				src/minirt/app/render/normal_rays/compute_normal_ray_on_sphere.c \
				src/minirt/app/render/reflection/reflection.c \
				src/minirt/app/render/render_canvas.c \
				src/minirt/app/render/render_fast_on_front_canvas.c \
				src/minirt/app/render/render_next_pixels_til_tmax_on_back_canvas.c \
				src/minirt/app/render/render_ray_from_camera.c \
				src/minirt/app/render/render_ray_on_object.c \
				src/minirt/app/render/transparency/compute_refracted_color.c \
				src/minirt/app/scene/camera_compute_constants.c \
				src/minirt/app/scene/cylinder_compute_constants.c \
				src/minirt/app/scene/plane_compute_constants.c \
				src/minirt/app/scene/scene_add_object.c \
				src/minirt/app/scene/scene_del.c \
				src/minirt/app/scene/sphere_compute_constants.c \
				src/minirt/app/utils/color/color_scale.c \
				src/minirt/app/utils/color/color_to_int.c \
				src/minirt/app/utils/drawings/img_draw_divider.c \
				src/minirt/app/utils/drawings/img_draw_square.c \
				src/minirt/app/utils/drawings/img_fill.c \
				src/minirt/app/utils/geometry/mat_product.c \
				src/minirt/app/utils/geometry/vec3_add.c \
				src/minirt/app/utils/geometry/vec3.c \
				src/minirt/app/utils/geometry/vec3_cross.c \
				src/minirt/app/utils/geometry/vec3_dot.c \
				src/minirt/app/utils/geometry/vec3_dot_xyz.c \
				src/minirt/app/utils/geometry/vec3_linear_transform.c \
				src/minirt/app/utils/geometry/vec3_normalize.c \
				src/minirt/app/utils/geometry/vec3_normalize_into.c \
				src/minirt/app/utils/geometry/vec3_norm.c \
				src/minirt/app/utils/geometry/vec3_scale.c \
				src/minirt/app/utils/geometry/vec3_scale_into.c \
				src/minirt/app/utils/geometry/vec3_substract.c \
				src/minirt/app/utils/geometry/vec3_substract_into.c \
				src/minirt.c \
				src/minirt/parser/directives/parse_ambient_light.c \
				src/minirt/parser/directives/parse_camera.c \
				src/minirt/parser/directives/parse_cylinder.c \
				src/minirt/parser/directives/parse_plane.c \
				src/minirt/parser/directives/parse_sphere.c \
				src/minirt/parser/directives/parse_spotlight.c \
				src/minirt/parser/error_logs/put_directive_error.c \
				src/minirt/parser/error_logs/put_field_error.c \
				src/minirt/parser/error_logs/put_unknown_directive_error.c \
				src/minirt/parser/fast_get_next_line/fast_get_next_line.c \
				src/minirt/parser/fast_get_next_line/fast_get_next_line_utils.c \
				src/minirt/parser/fields/parse_brightness.c \
				src/minirt/parser/fields/parse_color.c \
				src/minirt/parser/fields/parse_diameter.c \
				src/minirt/parser/fields/parse_direction.c \
				src/minirt/parser/fields/parse_float.c \
				src/minirt/parser/fields/parse_fov.c \
				src/minirt/parser/fields/parse_png.c \
				src/minirt/parser/fields/parse_vec3.c \
				src/minirt/parser/parse_directive.c \
				src/minirt/parser/parse_field.c \
				src/minirt/parser/parse_file.c \
				src/minirt/parser/parse_lines.c
BUILD		:=	.build
endif

INCLUDES	:=	$(SRC) lib/libft/include lib/mlx42/include

#==============================================================================#
#==== COMPILATION =============================================================#

CC			:=	clang									\

CFLAGS		:=	-std=c99 -Wall -Wextra -Werror			\
				-Wunreachable-code -Ofast				\

CPPFLAGS	:=	-MP -MMD $(addprefix -I,$(INCLUDES))	\

LDFLAGS		:=	-Llib/libft -lft						\
				-Llib/mlx42/build -lmlx42				\
				-ldl -lglfw -pthread -lm				\

ifdef DEBUG
CFLAGS		+=	-gdwarf-4 -Wno-unused-function
endif

#==============================================================================#
#==== BUILD FILES =============================================================#

OBJS	:=	$(SRCS:%.c=$(BUILD)/%.o)
DEPS	:=	$(SRCS:%.c=$(BUILD)/%.d)
DIRS	:=	$(sort $(shell dirname $(BUILD) $(OBJS)))

#******************************************************************************#
#**** PHONY RULES *************************************************************#

.PHONY:	all				\
		libft objs		\
		clean fclean re	\
		bonus

all: | $(LIBMLX42)					#build mlx42 once (and first)
all: objs libft $(NAME)				#build other targets every time needed

libft:								#libft may be updated during development,
	$(MAKE) -C lib/libft			#hence it's made a phony target

objs:								#build objs in parallel
	$(MAKE) -j$(nproc) $(OBJS)

clean:
	#clean libft
	$(MAKE) -C lib/libft clean
	#clean minirt
	$(info $(RED)Deleting objects$(NOC))
	rm -rf $(BUILD) $(BUILD_BONUS)

fclean: clean
	#full clean libft
	$(MAKE) -C lib/libft fclean
	#clean libmlx42
	rm -rf lib/mlx42/build
	#full clean minirt
	$(info $(RED)Deleting binary$(NOC))
	rm -rf $(NAME)

re: fclean all

bonus:
	$(MAKE) BONUS=42

#******************************************************************************#
#**** BUILD RULES *************************************************************#

$(LIBMLX42):
	cmake lib/mlx42 -B lib/mlx42/build						\
		&& cmake --build lib/mlx42/build -j$(nproc) -- -s

$(NAME): $(OBJS) $(LIBFT) $(LIBMLX42)
	$(info $(BLUE)Linking C executable $@$(NOC))
	$(CC) $(CFLAGS) $(OBJS) $(LDFLAGS) -o $@
	$(info $(GREEN)All done$(NOC))

$(DIRS):
	mkdir -p $@

$(OBJS): $(BUILD)/%.o: %.c | $$(@D)
	$(progress-log)
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

-include $(DEPS)

#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%#
#%%%% COLORS %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%#

NOC			:=	$(shell printf "\033[0m")
RED			:=	$(shell printf "\e[1m\e[38;5;196m")
BLUE		:=	$(shell printf "\e[1m\e[38;5;33m")
GREEN		:=	$(shell printf "\e[1m\e[38;5;76m")
PURPLE		:=	$(shell printf "\033[1;35m")

#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%#
#%%%% PROGRESS LOG UTILS %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%#

objs: export N		:=	0

ifdef BONUS
objs: export NTOTAL	?=	$(shell $(MAKE) BONUS=42 NTOTAL=1 -n $(OBJS) | grep clang | wc -l)
else
objs: export NTOTAL	?=	$(shell $(MAKE) NTOTAL=1 -n $(OBJS) | grep clang | wc -l)
endif

define progress-log =
	$(info [$(words $(N))/$(NTOTAL)] $(PURPLE)Building $< $(NOC))
	$(eval N += 1)
endef
