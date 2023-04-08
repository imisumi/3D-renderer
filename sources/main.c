/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichiro <ichiro@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 16:29:08 by ichiro            #+#    #+#             */
/*   Updated: 2023/04/08 04:31:56 by ichiro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/renderer.h"

t_triangle	triangles_to_render[N_MESH_FACES];

t_vec3	camera_position = {0, 0, -5};
t_vec3	cube_rotation = {0, 0, 0};

bool	is_running = false;
int		previous_frame_time = 0;

float	fov_factor = 640;

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

	WIDTH = get_window_width();
	HEIGHT = get_window_height();

	cube_rotation.x += 0.001;
	cube_rotation.y += 0.001;
	cube_rotation.z += 0.001;

	for (int i = 0; i < N_MESH_FACES; i++)
	{
		t_face	mesh_face = mesh_faces[i];
		
		t_vec3	face_vertices[3];
		face_vertices[0] = mesh_vertices[mesh_face.a -1];
		face_vertices[1] = mesh_vertices[mesh_face.b -1];
		face_vertices[2] = mesh_vertices[mesh_face.c -1];

		t_triangle	projected_triangle;
		for (int j = 0; j < 3; j++)
		{
			t_vec3	transform_vertex = face_vertices[j];
			
			transform_vertex = vec3_rotate_x(transform_vertex, cube_rotation.x);
			transform_vertex = vec3_rotate_y(transform_vertex, cube_rotation.y);
			transform_vertex = vec3_rotate_z(transform_vertex, cube_rotation.z);

			transform_vertex.z -= camera_position.z;

			t_vec2	projected_point = project(transform_vertex);

			projected_point.x += (WIDTH / 2);
			projected_point.y += (HEIGHT / 2);
			
			projected_triangle.points[j] = projected_point;
		}
		triangles_to_render[i] = projected_triangle;
	}
	
	// for (int i = 0; i < N_POINTS; i++)
	// {
	// 	t_vec3	point = cube_points[i];

	// 	t_vec3	transform_point = vec3_rotate_x(point, cube_rotation.x);
	// 	transform_point = vec3_rotate_y(transform_point, cube_rotation.y);
	// 	transform_point = vec3_rotate_z(transform_point, cube_rotation.z);

	// 	transform_point.z -= camera_position.z;

	// 	t_vec2	projected_point = project(transform_point);
	// 	projected_points[i] = projected_point;
	// }
}

void	render(void)
{
	WIDTH = get_window_width();
	HEIGHT = get_window_height();
	// draw_grid();
	// draw_rect(300, 100, 300, 150, BLUE);
	// draw_pixel(100, 300, BLUE);
	// draw_line(200, 300, 900, 500, BLUE);
	
	// for (int i = 0; i < N_POINTS; i++)
	// {
	// 	t_vec2 projected_point = projected_points[i];
	// 	draw_rect(projected_point.x + (WIDTH / 2), projected_point.y + (HEIGHT / 2), 2, 2, BLUE);
	// }
	for (int i = 0; i < N_MESH_FACES; i++)
	{
		t_triangle	triangle = triangles_to_render[i];
		// draw vertex points
		draw_rect(triangle.points[0].x, triangle.points[0].y, 2, 2, BLUE);
		draw_rect(triangle.points[1].x, triangle.points[1].y, 2, 2, BLUE);
		draw_rect(triangle.points[2].x, triangle.points[2].y, 2, 2, BLUE);

		// draw triangle lines
		draw_triangle(
			triangle.points[0].x,
			triangle.points[0].y,
			triangle.points[1].x,
			triangle.points[1].y,
			triangle.points[2].x,
			triangle.points[2].y,
			BLUE
			);
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
