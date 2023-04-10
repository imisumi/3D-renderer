/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mes                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichiro <ichiro@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 19:45:50 by ichiro            #+#    #+#             */
/*   Updated: 2023/04/07 20:18:58 by ichiro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/renderer.h"

t_mesh	mesh = {
	NULL,
	NULL,
	{0, 0, 0}
};

t_vec3	cube_vertices[N_CUBE_VERTICES] = {
	{-1, -1, -1}, // 1
	{-1, 1, -1}, // 2
	{1, 1, -1}, // 3
	{1, -1, -1}, // 4
	{1, 1, 1}, // 5
	{1, -1, 1}, // 6
	{-1, 1, 1}, // 7
	{-1, -1, 1}  // 8
};

t_face	cube_faces[N_CUBE_FACES] = {
	// front
	{1, 2, 3},
	{1, 3, 4},
	// right
	{4, 3, 5},
	{4, 5, 6},
	// back
	{6, 5, 7},
	{6, 7, 8},
	// left
	{8, 7, 2},
	{8, 2, 1},
	// top
	{2, 7, 5},
	{2, 5, 3},
	// botto
	{6, 8, 1},
	{6, 1, 4}
};

void	load_cube_mesh_data(void)
{
	for (int i = 0; i < N_CUBE_VERTICES; i++)
	{
		t_vec3	cube_vertex = cube_vertices[i];
		array_push(mesh.vertices, cube_vertex);
	}
	for (int i = 0; i < N_CUBE_FACES; i++)
	{
		t_face	cube_face = cube_faces[i];
		array_push(mesh.faces, cube_face);
	}
}

void	load_obj_file_data(char *filename)
{
	int		i;
	int		fd;
	char	*line;

	fd = open(filename, O_RDONLY);
	i = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (!line || line[0] == '\0')
			break ;
		if (!strncmp(line, "v ", 2))
		{
			t_vec3	vertex;
			sscanf(line, "v %f %f %f", &vertex.x, &vertex.y, &vertex.z);
			array_push(mesh.vertices, vertex);
			// printf("%s", line);
		}
		if (!strncmp(line, "f ", 2))
		{
			int	vertex_indices[3];
			int	textrure_indices[3];
			int	normal_indices[3];
			sscanf(line, "f %d/%d/%d %d/%d/%d %d/%d/%d",
			&vertex_indices[0], &textrure_indices[0], &normal_indices[0],
			&vertex_indices[1], &textrure_indices[1], &normal_indices[1],
			&vertex_indices[2], &textrure_indices[2], &normal_indices[2]
			);
			t_face	face = {
				vertex_indices[0],
				vertex_indices[1],
				vertex_indices[2]
			};
			array_push(mesh.faces, face);
			// printf("%s", line);
		}
		free(line);
	}
}