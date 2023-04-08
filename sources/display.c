/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichiro <ichiro@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 16:29:24 by ichiro            #+#    #+#             */
/*   Updated: 2023/04/08 03:4538 by ichiro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/renderer.h"

SDL_Window		*window = NULL;
SDL_Renderer	*renderer = NULL;
uint32_t		*color_buffer = NULL;
SDL_Texture		*color_buffer_texture = NULL;
int				WIDTH = 1080;
int				HEIGHT = 1080;

int	get_window_width(void)
{
	SDL_DisplayMode	display_mode;
	SDL_GetCurrentDisplayMode(0, &display_mode);
	return (display_mode.w);
}

int	get_window_height(void)
{
	SDL_DisplayMode	display_mode;
	SDL_GetCurrentDisplayMode(0, &display_mode);
	return (display_mode.h);
}

void	destroy_window(void)
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

bool	init_window(void)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		fprintf(stderr, "Error initializing SDL\n");
		return (false);
	}
	WIDTH = get_window_width();
	HEIGHT = get_window_height();
	// Create a SDL window
	// With borber
	window = SDL_CreateWindow("Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, 0);
	if (!window)
	{
		fprintf(stderr, "Error creating SDL window\n");
		return (false);
	}
	// Create a SDL renderer
	renderer = SDL_CreateRenderer(window, -1, 0);
	if (!renderer)
	{
		fprintf(stderr, "Error creating SDL renderer\n");
		return (false);
	}
	SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);
	return (true);
}

void	render_color_buffer(void)
{
	WIDTH = get_window_width();
	HEIGHT = get_window_height();

	SDL_UpdateTexture(color_buffer_texture, NULL, color_buffer, WIDTH * sizeof(uint32_t));
	SDL_RenderCopy(renderer, color_buffer_texture, NULL, NULL);
}

void	clear_color_buffer(uint32_t color)
{
	WIDTH = get_window_width();
	HEIGHT = get_window_height();
	// printf("width = %d\n", WIDTH);

	for (int y = 0; y < HEIGHT;  y++)
		for (int x = 0; x < WIDTH; x++)
			color_buffer[(WIDTH * y) + x] = color;
}

void	draw_grid(void)
{
	WIDTH = get_window_width();
	HEIGHT = get_window_height();
	// printf("width = %d\n", WIDTH);

	for (int y = 0; y < HEIGHT; y++)
		for (int x = 0; x < WIDTH; x++)
			if (y % 20 == 0 || x % 20 == 0)
				color_buffer[(WIDTH * y) + x] = 0x6a5acd;
}

void	draw_pixel(int x, int y, uint32_t color)
{
	WIDTH = get_window_width();
	HEIGHT = get_window_height();
	if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
		color_buffer[(WIDTH * y) + x] = color;
}

// void	draw_rect(int x, int y, int width, int height, uint32_t color)
// {
// 	for (int yy = y; yy < height + y; yy++)
// 		for (int xx = x; xx < width + x; xx++)
// 		{
// 			draw_pixel(xx, yy, color);
// 			color_buffer[(WIDTH * yy) + xx] = color;
// 		}
// }

void	draw_rect(int x, int y, int width, int height, uint32_t color)
{
	for (int i = 0; i < width; i++)
		for (int j = 0; j < height; j++)
		{
			int	cx = x + i;
			int	cy = y + j;
			draw_pixel(cx, cy, color);
			// color_buffer[(WIDTH * cy) + cx] = color;
		}
}

void	draw_triangle(int x1, int y1, int x2, int y2, int x3, int y3, uint32_t color)
{
	draw_line(x1, y1, x2, y2, color);
	draw_line(x2, y2, x3, y3, color);
	draw_line(x3, y3, x1, y1, color);
}

void	draw_line(int x1, int y1, int x2, int y2, uint32_t color)
{
	int	dx = abs(x2 - x1);
	int	dy = abs(y2 - y1);
	int	sx = (x1 < x2) ? 1 : -1;
	int	sy = (y1 < y2) ? 1 : -1;
	int	err = dx - dy;
	int	e2;
	while (1)
	{
		// mlx_put_pixel(data->image, x1, y1, 0xffffff);
		draw_pixel(x1, y1, color);
		if (x1 == x2 && y1 == y2)
			break ;
		e2 = 2 * err;
		if (e2 > -dy)
		{
			err -= dy;
			x1 += sx;
		}
		if (e2 < dx)
		{
			err += dx;
			y1 += sy;
		}
	}
}
