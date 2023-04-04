#include <stdio.h>
#include <stdbool.h>
#include "main.h"

bool	is_running = false;
SDL_Window	*window = NULL;
SDL_Renderer	*renderer = NULL;
uint32_t	*color_buffer = NULL;
SDL_Texture	*color_buffer_texture = NULL;
int	WIDTH = 1080;
int	HEIGHT = 1080;

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

void	setup(void)
{

	WIDTH = get_window_width();
	HEIGHT = get_window_height();

	color_buffer = malloc(sizeof(uint32_t) * WIDTH * HEIGHT);
	color_buffer_texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, WIDTH, HEIGHT);
}

void	process_input(void)
{
	SDL_Event	event;

	SDL_PollEvent(&event);

	switch (event.type)
	{
		case SDL_QUIT:
			is_running = false;
			break ;
		case SDL_KEYDOWN:
			if (event.key.keysym.sym == SDLK_ESCAPE)
			is_running = false;
			break ;
	}
}

void	update(void)
{

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

void	draw_rect(int x, int y, int width, int height, uint32_t color)
{
	for (int i = y; i < height + y; i++)
		for (int j = x; j < width + x; j++)
		{
			color_buffer[(WIDTH * i) + j] = color;
		}
	// int temp = x;
	// while (y < height)
	// {
	// 	x = temp;
	// 	while (x < width)
	// 	{
	// 		color_buffer[(WIDTH * y) + x] = color;
	// 		x++;
	// 	}
	// 	y++;
	// }
}

void	render(void)
{
	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
	SDL_RenderClear(renderer);

	// draw_grid();
	draw_rect(300, 200, 300, 150, 0x6a5acd);
	render_color_buffer();
	clear_color_buffer(0xFFFFFF00);

	SDL_RenderPresent(renderer);
}

void	destroy_window(void)
{
	free(color_buffer);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

int	main(void)
{
	is_running = init_window();

	setup();

	while (is_running)
	{
		process_input();
		update();
		render();
	}

	destroy_window();
	return (0);
}
