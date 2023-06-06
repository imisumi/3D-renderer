/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichiro <ichiro@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 16:29:17 by ichiro            #+#    #+#             */
/*   Updated: 2023/06/06 03:35:21 by ichiro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATRIX_H
#define MATRIX_H

#include "renderer.h"

typedef struct	s_mat4 {
	float	m[4][4];
}	t_mat4;

t_mat4	mat4_make_identity(void);
t_mat4	mat4_make_scale(float sx, float sy, float sz);
t_mat4	mat4_make_translation(float tx, float ty, float tz);
t_mat4	mat4_make_rotation(float angle_rad);
t_mat4	mat4_make_rotation_x(float angle);
t_mat4	mat4_make_rotation_y(float angle);
t_mat4	mat4_make_rotation_z(float angle);

t_vec4	mat4_mul_vec4(t_mat4 m, t_vec4 v);
t_mat4	mat4_mul_mat4(t_mat4 a, t_mat4 b);

t_mat4 mat4_make_perspective(float fov, float aspect, float znear, float zfar);
t_vec4	mat4_mul_vec4_project(t_mat4 mat_prok, t_vec4 v);

#endif