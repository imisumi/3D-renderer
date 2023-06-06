/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mesh.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichiro <ichiro@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 16:29:17 by ichiro            #+#    #+#             */
/*   Updated: 2023/06/04 21:23:31 by ichiro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MESH_H
#define MESH_H

#include "vector.h"
#include "triangle.h"

#define N_CUBE_VERTICES 8
#define N_CUBE_FACES (6 * 2) // 6 cube faces, 2 triangles per face

extern t_vec3 cube_vertices[N_CUBE_VERTICES];
extern t_face cube_faces[N_CUBE_FACES];

typedef struct s_mesh
{
	t_vec3	*vertices;	// dynamic array of vertices
	t_face	*faces;
	t_vec3	rotation;
	t_vec3	scale;
	t_vec3	translation;
}	t_mesh;

extern t_mesh	mesh;

void	load_cube_mesh_data(void);
void	load_obj_file_data(char *filename);

#endif