/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdubois <tdubois@student.42angouleme.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 08:39:22 by tdubois           #+#    #+#             */
/*   Updated: 2023/06/05 11:26:56 by tdubois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEBUG_H
# define DEBUG_H

# include <stdbool.h>
# include <stdio.h>

extern bool	g_is_debugging;

#define DEBUG(...) if (g_is_debugging) fprintf(stderr, __VA_ARGS__);

#define DEBUG_COLOR(color) DEBUG("color: %f %f %f\n", color.r, color.g, color.b);
#define DEBUG_COLORP(color) DEBUG("color: %f %f %f\n", color->r, color->g, color->b);

#define DEBUG_ON()  g_is_debugging = true;
#define DEBUG_OFF() g_is_debugging = false;


#endif//DEBUG_H
