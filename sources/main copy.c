/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichiro <ichiro@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 16:29:08 by ichiro            #+#    #+#             */
/*   Updated: 2023/04/07 19:38:01 by ichiro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/renderer.h"

bool	is_running = false;
int		previous_frame_time = 0;

const int	N_POINTS = 9 * 9 * 9;
t_vec3	cube_points[N_POINTS];
t_vec2	projected_points[N_POINTS];

t_vec3	camera_position = {0, 0, -5};
t_vec3	cube_rotation = {0, 0, 0};
// t_vec3	camera_position = {.x = 0, .y = 0, .z = -5};

float	fov_factor = 640;

void	setup(void)
{

	WIDTH = get_window_width();
	HEIGHT = get_window_height();

	color_buffer = malloc(sizeof(uint32_t) * WIDTH * HEIGHT);
	color_buffer_texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, WIDTH, HEIGHT);
	
	int	i = 0;
	for (float x = -1; x <= 1; x += 0.25)
		for (float y = -1; y <= 1; y += 0.25)
			for (float z = -1; z <= 1; z += 0.25)
			{
				t_vec3	new_point = {.x = x, .y = y, .z = z};
				cube_points[i] = new_point;
				i++;
			}
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

t_vec2	project(t_vec3 point)
{
	t_vec2	projected_point = {
			.x = (fov_factor * point.x) / point.z,
			.y = (fov_factor * point.y) / point.z
			};

	return (projected_point);
}

void	update(void)
{
	while (!SDL_TICKS_PASSED(SDL_GetTicks(), previous_frame_time + FRAME_TARGET_TIME));
	previous_frame_time = SDL_GetTicks();

	cube_rotation.x += 0.01;
	cube_rotation.y += 0.01;
	cube_rotation.z += 0.01;
	for (int i = 0; i < N_POINTS; i++)
	{
		t_vec3	point = cube_points[i];

		t_vec3	transform_point = vec3_rotate_x(point, cube_rotation.x);
		transform_point = vec3_rotate_y(transform_point, cube_rotation.y);
		transform_point = vec3_rotate_z(transform_point, cube_rotation.z);

		transform_point.z -= camera_position.z;

		t_vec2	projected_point = project(transform_point);
		projected_points[i] = projected_point;
	}
}

void	render(void)
{
	WIDTH = get_window_width();
	HEIGHT = get_window_height();
	// draw_grid();
	// draw_rect(300, 100, 300, 150, BLUE);
	// draw_pixel(100, 300, BLUE);
	
	for (int i = 0; i < N_POINTS; i++)
	{
		t_vec2 projected_point = projected_points[i];
		draw_rect(projected_point.x + (WIDTH / 2), projected_point.y + (HEIGHT / 2), 2, 2, BLUE);
	}
	
	render_color_buffer();
	clear_color_buffer(WHITE);

	SDL_RenderPresent(renderer);
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
