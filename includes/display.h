/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichiro <ichiro@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 16:29:17 by ichiro            #+#    #+#             */
/*   Updated: 2023/04/08 04:20:12 by ichiro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DISPLAY_H
#define DISPLAY_H

#include <stdint.h>
#include <stdbool.h>
#include "/opt/homebrew/Cellar/sdl2/2.26.4/include/SDL2/SDL.h"

#define FPS 60 
#define FRAME_TARGET_TIME (1000 / FPS)

extern SDL_Window* window;
extern SDL_Renderer* renderer;
extern uint32_t* color_buffer;
extern SDL_Texture* color_buffer_texture;
extern int WIDTH;
extern int HEIGHT;

bool	init_window(void);
void	draw_grid(void);
void	draw_pixel(int x, int y, uint32_t color);
void	draw_rect(int x, int y, int width, int height, uint32_t color);
void	render_color_buffer(void);
void	clear_color_buffer(uint32_t color);
void	destroy_window(void);
int		get_window_width(void);
int		get_window_height(void);
void	draw_line(int x1, int y1, int x2, int y2, uint32_t color);
void	draw_triangle(int x1, int y1, int x2, int y2, int x3, int y3, uint32_t color);

#endif
