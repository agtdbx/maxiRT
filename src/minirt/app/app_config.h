/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   app_config.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouba <aderouba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 11:49:06 by tdubois           #+#    #+#             */
/*   Updated: 2023/07/06 18:31:44 by aderouba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef APP_CONFIG_H
# define APP_CONFIG_H

# include <stdint.h>

//---- WINDOW ----------------------------------------------------------------//

static const char		*g_window_title = "maxiRT";
static const int32_t	g_window_width = 1920;
static const int32_t	g_window_height = 1080;

//---- MENU ------------------------------------------------------------------//

static const int32_t	g_menu_width = 400;
static const int32_t	g_menu_background_color = 0x333333FF;
static const int32_t	g_menu_dividers_color = 0x666666FF;
static const int32_t	g_menu_divider_1_y = 140;
static const int32_t	g_menu_divider_2_y = 280;

//---- REFLECTION_CONSTANTS --------------------------------------------------//

static const float		g_ambient_light_ratio = 0.2f;
static const float		g_diffuse_light_ratio = 0.5f;
static const float		g_specular_light_ratio = 0.3f;
static const float		g_phong_exponent = 42.0f;

static const float		g_opacity_color_ratio = 1.0f / 255.0f;

//---- scene -----------------------------------------------------------------//

static const float		g_scene_radius = 1000.0f;

// sphere
static const float		g_sphere_default_reflection = 0.0f;
static const float		g_sphere_default_opacity = 1.0f;
static const float		g_sphere_default_density = 1.0f;

// plane
static const float		g_plane_default_reflection = 0.0f;
static const float		g_plane_default_opacity = 1.0f;
static const float		g_plane_default_density = 1.0f;

// cylinder
static const float		g_cylinder_default_reflection = 0.0f;
static const float		g_cylinder_default_opacity = 1.0f;
static const float		g_cylinder_default_density = 1.0f;

// cone
static const float		g_cone_default_reflection = 0.0f;
static const float		g_cone_default_opacity = 1.0f;
static const float		g_cone_default_density = 1.0f;

// cube
static const float		g_cube_default_reflection = 0.0f;
static const float		g_cube_default_opacity = 1.0f;
static const float		g_cube_default_density = 1.0f;

//---- MATHS -----------------------------------------------------------------//

static const float		g_pi = 3.141592f;
static const float		g_pi_div_180 = 0.017453f;
static const float		g_pi_div_360 = 0.008726f;

//---- COLORS ----------------------------------------------------------------//

static const int32_t	g_color_black = 0xFF;

#endif//APP_CONFIG_H
