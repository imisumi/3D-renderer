/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mesh.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichiro <ichiro@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 16:29:17 by ichiro            #+#    #+#             */
/*   Updated: 2023/04/07 20:27:19 by ichiro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MESH_H
#define MESH_H

#include "vector.h"
#include "triangle.h"

#define N_MESH_VERTICES 8
extern t_vec3 mesh_vertices[N_MESH_VERTICES];

#define N_MESH_FACES (6 * 2) // 6 cube faces, 2 triangles per face
extern t_face mesh_faces[N_MESH_FACES];

#endif