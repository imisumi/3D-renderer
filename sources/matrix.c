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

// | 1 0 0 0 |
// | 0 1 0 0 |
// | 0 0 1 0 |
// | 0 0 0 1 |
t_mat4	mat4_make_identity(void)
{
	t_mat4	mat = {{
		{1.0f, 0.0f, 0.0f, 0.0f},
		{0.0f, 1.0f, 0.0f, 0.0f},
		{0.0f, 0.0f, 1.0f, 0.0f},
		{0.0f, 0.0f, 0.0f, 1.0f}
	}};
	return (mat);
}

// | sx 0  0  0 |
// | 0  sy 0  0 |
// | 0  0  sz 0 |
// | 0  0  0  1 |
t_mat4	mat4_make_scale(float sx, float sy, float sz)
{
	t_mat4	mat = mat4_make_identity();
	mat.m[0][0] = sx;
	mat.m[1][1] = sy;
	mat.m[2][2] = sz;
	return (mat);
}

// | 1 0 0 tx |
// | 0 1 0 ty |
// | 0 0 1 tz |
// | 0 0 0 1  |
t_mat4	mat4_make_translation(float tx, float ty, float tz)
{
	t_mat4	mat = mat4_make_identity();
	mat.m[0][3] = tx;
	mat.m[1][3] = ty;
	mat.m[2][3] = tz;
	return (mat);
}

t_mat4	mat4_make_rotation_x(float angle)
{
	t_mat4	mat = mat4_make_identity();
	float	s = sinf(angle);
	float	c = cosf(angle);

	
	mat.m[0][0] = c;
	mat.m[0][1] = -s;
	mat.m[1][0] = s;
	mat.m[1][1] = c;
	return (mat);
}

t_mat4	mat4_make_rotation_y(float angle)
{
	t_mat4	mat = mat4_make_identity();
	float	s = sinf(angle);
	float	c = cosf(angle);

	mat.m[1][1] = c;
	mat.m[1][2] = -s;
	mat.m[2][1] = s;
	mat.m[2][2] = c;
	return (mat);
}

t_mat4	mat4_make_rotation_z(float angle)
{
	t_mat4	mat = mat4_make_identity();
	float	s = sinf(angle);
	float	c = cosf(angle);

	mat.m[0][0] = c;
	mat.m[0][2] = s;
	mat.m[2][0] = -s;
	mat.m[2][2] = c;
	return (mat);
}



t_vec4	mat4_mul_vec4(t_mat4 m, t_vec4 v)
{
	t_vec4	res;

	res.x = m.m[0][0] * v.x + m.m[0][1] * v.y + m.m[0][2] * v.z + m.m[0][3] * v.w;
	res.y = m.m[1][0] * v.x + m.m[1][1] * v.y + m.m[1][2] * v.z + m.m[1][3] * v.w;
	res.z = m.m[2][0] * v.x + m.m[2][1] * v.y + m.m[2][2] * v.z + m.m[2][3] * v.w;
	res.w = m.m[3][0] * v.x + m.m[3][1] * v.y + m.m[3][2] * v.z + m.m[3][3] * v.w;
	return (res);
}

t_mat4	mat4_mul_mat4(t_mat4 a, t_mat4 b)
{
	t_mat4 m;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			m.m[i][j] = a.m[i][0] * b.m[0][j] +
						a.m[i][1] * b.m[1][j] +
						a.m[i][2] * b.m[2][j] +
						a.m[i][3] * b.m[3][j];
		}
	}
	return (m);
}

// t_mat4	mat4_mul_mat4(t_mat4 a, t_mat4 b)
// {
// 	t_mat4 m;
// 	for (int i = 0; i < 4; i++) {
// 		for (int j = 0; j < 4; j++) {
// 			for (int k =0; k < 4; k++) {
// 				m.m[i][j] += a.m[i][k] * b.m[k][j];
// 			}
// 		}
// 	}
// 	return (m);
// }

//
t_mat4 mat4_make_perspective(float fov, float aspect, float znear, float zfar)
{
	t_mat4 m = {{{0}}};
	float tan_half_fov = tanf(fov / 2.0f);
	m.m[0][0] = aspect * (1.0f / tan_half_fov);
	m.m[1][1] = 1.0f / tan_half_fov;
	m.m[2][2] = zfar / (zfar - znear);
	m.m[2][3] = (-zfar * znear) / (zfar - znear);
	m.m[3][2] = 1.0f;
	return (m);
}

t_vec4	mat4_mul_vec4_project(t_mat4 mat_proj, t_vec4 v)
{
	t_vec4 res = mat4_mul_vec4(mat_proj, v);
	if (res.w != 0.0f)
	{
		res.x /= res.w;
		res.y /= res.w;
		res.z /= res.w;
	}
	return (res);
}


