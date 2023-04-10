/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichiro <ichiro@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 16:29:08 by ichiro            #+#    #+#             */
/*   Updated: 2023/04/09 0534:5 by ichiro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/renderer.h"

// t_triangle	triangles_to_render[N_MESH_FACES];
t_triangle	*triangles_to_render = NULL;

t_vec3	camera_position = {0, 0, 0};
// t_vec3	cube_rotation = {0, 0, 0};

bool	is_running = false;
int		previous_frame_time = 0;

float	fov_factor = 640;

void	setup(void)
{

	WIDTH = get_window_width();
	HEIGHT = get_window_height();

	color_buffer = malloc(sizeof(uint32_t) * WIDTH * HEIGHT);
	color_buffer_texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, WIDTH, HEIGHT);
	
	// load_cube_mesh_data();
	load_obj_file_data("./assets/cube_tri.obj");
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

	// initilize the array of triangle to render
	triangles_to_render = NULL;

	mesh.rotation.x += 0.007;
	mesh.rotation.y += 0.01;
	mesh.rotation.z += 0.003;

	int	num_faces = array_length(mesh.faces);
	for (int i = 0; i < num_faces; i++)
	{
		t_face	mesh_face = mesh.faces[i];
		
		t_vec3	face_vertices[3];
		face_vertices[0] = mesh.vertices[mesh_face.a -1];
		face_vertices[1] = mesh.vertices[mesh_face.b -1];
		face_vertices[2] = mesh.vertices[mesh_face.c -1];

		t_vec3	transformed_vertices[3];
		for (int j = 0; j < 3; j++)
		{
			t_vec3	transform_vertex = face_vertices[j];
			
			transform_vertex = vec3_rotate_x(transform_vertex, mesh.rotation.x);
			transform_vertex = vec3_rotate_y(transform_vertex, mesh.rotation.y);
			transform_vertex = vec3_rotate_z(transform_vertex, mesh.rotation.z);

			transform_vertex.z += 5;

			transformed_vertices[j] = transform_vertex;
		}
		// Check back face culling
		t_vec3	vector_a = transformed_vertices[0]; //    A
		t_vec3	vector_b = transformed_vertices[1]; //  / |
		t_vec3	vector_c = transformed_vertices[2]; // B--C

		// get vector substraction of B-A and C -A
		t_vec3	vector_ab = vec3_sub(vector_b, vector_a);
		t_vec3	vector_ac = vec3_sub(vector_c, vector_a);
		vec3_normalize(&vector_ab);
		vec3_normalize(&vector_ac);

		// compute the face normal
		t_vec3	normal = vec3_cross(vector_ab, vector_ac);
		vec3_normalize(&normal);

		t_vec3	camera_ray = vec3_sub(camera_position, vector_a);

		float	dot_normal_camera = vec3_dot(normal, camera_ray);

		if (dot_normal_camera < 0)
			continue;


		t_triangle	projected_triangle;
		for (int j = 0; j < 3; j++)
		{
			t_vec2	projected_point = project(transformed_vertices[j]);

			projected_point.x += (WIDTH / 2);
			projected_point.y += (HEIGHT / 2);
			
			projected_triangle.points[j] = projected_point;
		}
		// triangles_to_render[i] = projected_triangle;
		array_push(triangles_to_render, projected_triangle);
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

	// draw_triangle(100, 100, 1000, 50, 500, 700, BLUE);

	// draw_filled_triangle(100, 100, 1000, 50, 500, 700, BLUE);

	int	num_triangles = array_length(triangles_to_render);
	for (int i = 0; i < num_triangles; i++)
	{
		t_triangle	triangle = triangles_to_render[i];
		// draw vertex points
		draw_rect(triangle.points[0].x, triangle.points[0].y, 1, 1, BLUE);
		draw_rect(triangle.points[1].x, triangle.points[1].y, 1, 1, BLUE);
		draw_rect(triangle.points[2].x, triangle.points[2].y, 1, 1, BLUE);

		// draw_filled_triangle lines
		draw_filled_triangle(
			triangle.points[0].x, triangle.points[0].y,
			triangle.points[1].x, triangle.points[1].y,
			triangle.points[2].x, triangle.points[2].y,
			BLUE
			);
		draw_triangle(
			triangle.points[0].x, triangle.points[0].y,
			triangle.points[1].x, triangle.points[1].y,
			triangle.points[2].x, triangle.points[2].y,
			PINK
			);
	}
	
	array_free(triangles_to_render);
	// array_free(mesh)
	
	render_color_buffer();
	clear_color_buffer(WHITE);

	SDL_RenderPresent(renderer);
}

void	free_resources(void)
{
	free(color_buffer);
	array_free(mesh.faces);
	array_free(mesh.vertices);
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
	free_resources();
	return (0);
}
