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
		
	}
}