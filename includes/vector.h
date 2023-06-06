/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 16:29:17 by ichiro            #+#    #+#             */
/*   Updated: 2023/04/09 2:16:23 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_H
#define VECTOR_H

typedef struct s_vec2
{
	float	x;
	float	y;
}	t_vec2;

typedef struct s_vec3
{
	float	x;
	float	y;
	float	z;
}	t_vec3;

typedef struct s_vec4
{
	float	x;
	float	y;
	float	z;
	float	w;
}	t_vec4;

///////////////////////////////////////
// Vector 2D
///////////////////////////////////////
float	vec2_length(t_vec2 v);
t_vec2	vec2_add(t_vec2 a, t_vec2 b);
t_vec2	vec2_sub(t_vec2 a, t_vec2 b);
t_vec2	vec2_mul(t_vec2 a, float factor);
t_vec2	vec2_div(t_vec2 a, float factor);
float	vec2_dot(t_vec2 a, t_vec2 b);
void	vec2_normalize(t_vec2 *v);

///////////////////////////////////////
// Vector 3D
///////////////////////////////////////
float	vec3_length(t_vec3 v);
t_vec3	vec3_add(t_vec3 a, t_vec3 b);
t_vec3	vec3_sub(t_vec3 a, t_vec3 b);
t_vec3	vec3_mul(t_vec3 a, float factor);
t_vec3	vec3_div(t_vec3 a, float factor);
t_vec3	vec3_cross(t_vec3 a, t_vec3 b);
float	vec3_dot(t_vec3 a, t_vec3 b);
void	vec3_normalize(t_vec3 *v);

t_vec3 vec3_rotate_x(t_vec3 v, float angle);
t_vec3 vec3_rotate_y(t_vec3 v, float angle);
t_vec3 vec3_rotate_z(t_vec3 v, float angle);

///////////////////////////////////////
// Vector 4D
///////////////////////////////////////
t_vec4	vec4_from_vec3(t_vec3 v);
t_vec3	vec3_from_vec4(t_vec4 v);

// t_vec4	mat4_mul_vec4_project(t_mat4 mat_prok, t_vec4 v);

#endif
