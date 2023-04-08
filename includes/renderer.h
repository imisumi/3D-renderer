/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichiro <ichiro@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 16:29:17 by ichiro            #+#    #+#             */
/*   Updated: 2023/04/08 16:38:38 by ichiro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDERER_H
# define RENDERER_H

#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
#include "/opt/homebrew/Cellar/sdl2/2.26.4/include/SDL2/SDL.h"
#include "colors.h"
#include "display.h"
#include "mesh.h"
#include "triangle.h"
#include "vector.h"
#include "array.h"
#include "get_next_line.h"


// #define FPS 60
// #define FRAME_TARGET_TIME (1000 / FPS)


// extern SDL_Window	*window;
// extern SDL_Renderer	*renderer;
// extern uint32_t		*color_buffer;
// extern SDL_Texture	*color_buffer_texture;
// extern int	WIDTH;
// extern int	HEIGHT;

// typedef struct s_vec2
// {
// 	float	x;
// 	float	y;
// }	t_vec2;

// typedef struct s_vec3
// {
// 	float	x;
// 	float	y;
// 	float	z;
// }	t_vec3;

// typedef struct s_camera
// {
// 	t_vec3	position;
// 	t_vec3	rotation;
// 	float	fov_angle;
// }	t_camera;


// display.c
// bool	init_window(void);
// void	draw_grid(void);
// void	draw_pixel(int x, int, uint32_t color);
// void	draw_rect(int x, int y, int width, int height, uint32_t color);
// void	render_color_buffer(void);
// void	clear_color_buffer(uint32_t color);
// void	destroy_window(void);
// int		get_window_width(void);
// int		get_window_height(void);

// vector.c
// t_vec3 vec3_rotate_x(t_vec3 v, float angle);
// t_vec3 vec3_rotate_y(t_vec3 v, float angle);
// t_vec3 vec3_rotate_z(t_vec3 v, float angle);

//	mesh.c







#endif
