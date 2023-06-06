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

t_mat4	proj_matrix;

void	setup(void)
{
	render_method = RENDER_WIRE;
	cull_method = CULL_BACKFACE;

	WIDTH = get_window_width();
	HEIGHT = get_window_height();

	color_buffer = malloc(sizeof(uint32_t) * WIDTH * HEIGHT);
	color_buffer_texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, WIDTH, HEIGHT);
	
	//! init the perspective projection mattix
	float fov = M_PI / 3.0f;
	float aspect = (float)HEIGHT / (float)WIDTH;
	float znear = 0.1f;
	float zfar = 100.0f;
	proj_matrix = mat4_make_perspective(fov, aspect, znear, zfar);
	// load_cube_mesh_data();
	//load_obj_file_data("./assets/cube_tri.obj");
	load_cube_mesh_data();
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
			if (event.key.keysym.sym == SDLK_1)
				render_method = RENDER_WIRE_VERTEX;
			if (event.key.keysym.sym == SDLK_2)
				render_method = RENDER_WIRE;
			if (event.key.keysym.sym == SDLK_3)
				render_method = RENDER_FILL_TRIANGLE;
			if (event.key.keysym.sym == SDLK_4)
				render_method = RENDER_FILL_TRIANGLE_WIRE;
			if (event.key.keysym.sym == SDLK_c)
				cull_method = CULL_BACKFACE;
			if (event.key.keysym.sym == SDLK_d)
				cull_method = CULL_NONE;
			break ;
	}
}

// t_vec2	project(t_vec3 point)
// {
// 	t_vec2	projected_point = {
// 		.x = (fov_factor * point.x) / point.z,
// 		.y = (fov_factor * point.y) / point.z
// 		};

// 	return (projected_point);
// }



void	update(void)
{
	while (!SDL_TICKS_PASSED(SDL_GetTicks(), previous_frame_time + FRAME_TARGET_TIME));
	previous_frame_time = SDL_GetTicks();

	WIDTH = get_window_width();
	HEIGHT = get_window_height();

	// initilize the array of triangle to render
	triangles_to_render = NULL;

	// mesh.rotation.x += 0.01;
	mesh.rotation.y += 0.01;
	// mesh.rotation.z += 0.01;
	// mesh.scale.x += 0.002;
	// mesh.scale.y += 0.001;
	// mesh.translation.x += 0.01;
	mesh.translation.z = 5;


	t_mat4	scale_matrix = mat4_make_scale(mesh.scale.x, mesh.scale.y, mesh.scale.z);
	t_mat4	translation_matrix = mat4_make_translation(mesh.translation.x, mesh.translation.y, mesh.translation.z);
	t_mat4	rotation_matrix_x = mat4_make_rotation_x(mesh.rotation.x);
	t_mat4	rotation_matrix_y = mat4_make_rotation_y(mesh.rotation.y);
	t_mat4	rotation_matrix_z = mat4_make_rotation_z(mesh.rotation.z);

	int	num_faces = array_length(mesh.faces);
	for (int i = 0; i < num_faces; i++)
	{
		t_face	mesh_face = mesh.faces[i];
		
		t_vec3	face_vertices[3];
		face_vertices[0] = mesh.vertices[mesh_face.a -1];
		face_vertices[1] = mesh.vertices[mesh_face.b -1];
		face_vertices[2] = mesh.vertices[mesh_face.c -1];

		t_vec4	transformed_vertices[3];

		// loop all three vertices of this current face and apply transformation
		for (int j = 0; j < 3; j++)
		{
			t_vec4	transform_vertex = vec4_from_vec3(face_vertices[j]);
			
			//! World matrix
			t_mat4	world_matrix = mat4_make_identity();

			//? Order matters: First scale, then rotate, then translate
			world_matrix = mat4_mul_mat4(scale_matrix, world_matrix);
			world_matrix = mat4_mul_mat4(rotation_matrix_z, world_matrix);
			world_matrix = mat4_mul_mat4(rotation_matrix_y, world_matrix);
			world_matrix = mat4_mul_mat4(rotation_matrix_x, world_matrix);
			world_matrix = mat4_mul_mat4(translation_matrix, world_matrix);


			//! Multiply the world matrix by the original vector
			transform_vertex = mat4_mul_vec4(world_matrix, transform_vertex);



			transformed_vertices[j] = transform_vertex;
		}
		// Check back face culling
		if (cull_method == CULL_BACKFACE) {
			t_vec3	vector_a = vec3_from_vec4(transformed_vertices[0]); //    A
			t_vec3	vector_b = vec3_from_vec4(transformed_vertices[1]); //  / |
			t_vec3	vector_c = vec3_from_vec4(transformed_vertices[2]); // B--C

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

			if (dot_normal_camera < 0) {
				continue;
			}
		}


		//! Project
		t_vec4 projected_points[3];
		for (int j = 0; j < 3; j++)
		{
			// projected_points[j] = project(vec3_from_vec4(transformed_vertices[j]));
			projected_points[j] = mat4_mul_vec4_project(proj_matrix, transformed_vertices[j]);

			projected_points[j].x *= (WIDTH / 2.0f);
			projected_points[j].y *= (HEIGHT / 2.0f);

			projected_points[j].x += (WIDTH / 2.0f);
			projected_points[j].y += (HEIGHT / 2.0f);

		}

		// calculate the avarage depth of each face base on verices after transformation
		float avg_depth = (transformed_vertices[0].z + transformed_vertices[1].z + transformed_vertices[2].z) / 3.0;

		t_triangle	projected_triangle = {
			.points = {
				{projected_points[0].x, projected_points[0].y},
				{projected_points[1].x, projected_points[1].y},
				{projected_points[2].x, projected_points[2].y},
			},
			.color = mesh_face.color,
			.avg_depth = avg_depth
		};
		// triangles_to_render[i] = projected_triangle;
		array_push(triangles_to_render, projected_triangle);
	}
	
	// sort the triangles to render base on their avg_depth
	int num = array_length(triangles_to_render);
	for (int i = 0; i < num; i++) {
		for (int j = i; j < num; j++) {
			if (triangles_to_render[i].avg_depth < triangles_to_render[j].avg_depth) {
				t_triangle temp = triangles_to_render[i];
				triangles_to_render[i] = triangles_to_render[j];
				triangles_to_render[j] = temp;
			}
		}
	}
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
	for (int i = 0; i < num_triangles; i++) {
		t_triangle	triangle = triangles_to_render[i];
		

		// draw_filled_triangle lines
		if (render_method == RENDER_FILL_TRIANGLE|| render_method == RENDER_FILL_TRIANGLE_WIRE) {
			draw_filled_triangle(
				triangle.points[0].x, triangle.points[0].y,
				triangle.points[1].x, triangle.points[1].y,
				triangle.points[2].x, triangle.points[2].y,
				triangle.color
				);
		}
		// draw triangle wireframe
		if (render_method == RENDER_WIRE || render_method == RENDER_WIRE_VERTEX || render_method == RENDER_FILL_TRIANGLE_WIRE) {
			draw_triangle(
				triangle.points[0].x, triangle.points[0].y,
				triangle.points[1].x, triangle.points[1].y,
				triangle.points[2].x, triangle.points[2].y,
				PINK
				);
		}
		// draw vertex points
		if (render_method == RENDER_WIRE_VERTEX){
			draw_rect(triangle.points[0].x - 3, triangle.points[0].y - 3, 6, 6, BLUE);
			draw_rect(triangle.points[1].x - 3, triangle.points[1].y - 3, 6, 6, BLUE);
			draw_rect(triangle.points[2].x - 3, triangle.points[2].y - 3, 6, 6, BLUE);
		}
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
