/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichiro <ichiro@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 15:56:24 by ichiro            #+#    #+#             */
/*   Updated: 2023/04/09 22:33:595 by ichiro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/renderer.h"

float	vec2_length(t_vec2 v)
{
	return (sqrt(v.x * v.x + v.y * v.y));
}

t_vec2	vec2_add(t_vec2 a, t_vec2 b)
{
	t_vec2	result = {a.x + b.x, a.y + b.y};
	return (result);
}

t_vec2	vec2_sub(t_vec2 a, t_vec2 b)
{
	t_vec2	result = {a.x - b.x, a.y - b.y};
	return (result);
}

t_vec2	vec2_mul(t_vec2 v, float factor)
{
	t_vec2	result = {v.x * factor, v.y * factor};
	return (result);
}

t_vec2	vec2_div(t_vec2 v, float factor)
{
	t_vec2	result = {v.x / factor, v.y / factor};
	return (result);
}

float	vec2_dot(t_vec2 a, t_vec2 b)
{
	return (a.x * b.x + a.y * b.y);
}

void	vec2_normalize(t_vec2 *v)
{
	float	length = sqrt(v->x * v->x + v->y * v->y);
	v->x /= length;
	v->y /= length;
}

///////////////////////////////////////
// Vector 3D
///////////////////////////////////////

float	vet3_length(t_vec3 v)
{
	return (sqrt(v.x * v.x + v.y * v.y + v.z * v.z));
}

t_vec3	vec3_add(t_vec3 a, t_vec3 b)
{
	t_vec3	result = {
		a.x + b.x,
		a.y + b.y,
		a.z + b.z
		};
	return (result);
}

t_vec3	vec3_sub(t_vec3 a, t_vec3 b)
{
	t_vec3	result = {
		a.x - b.x,
		a.y - b.y,
		a.z - b.z
		};
	return (result);
}

t_vec3	vec3_mul(t_vec3 v, float factor)
{
	t_vec3	result = {
		v.x * factor,
		v.y * factor,
		v.z * factor
		};
	return (result);
}

t_vec3	vec3_div(t_vec3 v, float factor)
{
	t_vec3	result = {
		v.x / factor,
		v.y / factor,
		v.z / factor
		};
	return (result);
}

t_vec3	vec3_cross(t_vec3 a, t_vec3 b)
{
	t_vec3	result = {
		a.y * b.z - a.z * b.y,
		a.z * b.x - a.x * b.z,
		a.x * b.y - a.y * b.x
	};
	return (result);
}

float	vec3_dot(t_vec3 a, t_vec3 b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

void	vec3_normalize(t_vec3 *v)
{
	float	length = sqrt(v->x * v->x + v->y * v->y + v->z * v->z);
	v->x /= length;
	v->y /= length;
	v->z /= length;
}








t_vec3 vec3_rotate_x(t_vec3 v, float angle)
{
	t_vec3	rotate_vector = {
		v.x,
		v.y * cos(angle) - v.z * sin(angle),
		v.y * sin(angle) + v.z * cos(angle)
	};
	return (rotate_vector);
}

t_vec3 vec3_rotate_y(t_vec3 v, float angle)
{
	t_vec3	rotate_vector = {
		v.x * cos(angle) - v.z * sin(angle),
		v.y,
		v.x * sin(angle) + v.z * cos(angle)
	};
	return (rotate_vector);
}

t_vec3 vec3_rotate_z(t_vec3 v, float angle)
{
	t_vec3	rotate_vector = {
		v.x * cos(angle) - v.y * sin(angle),
		v.x * sin(angle) + v.y * cos(angle),
		v.z
	};
	return (rotate_vector);
}



t_vec4	vec4_from_vec3(t_vec3 v)
{
	t_vec4	result = {
		v.x,
		v.y,
		v.z,
		1.0f
	};
	return (result);
}

t_vec3	vec3_from_vec4(t_vec4 v)
{
	t_vec3	result = {
		v.x,
		v.y,
		v.z
	};
	return (result);
}


// t_vec4	mat4_mul_vec4_project(t_mat4 mat_proj, t_vec4 v)
// {
// 	t_vec4 res = mat4_mul_vec4(mat_proj, v);
// 	if (res.w != 0.0f)
// 	{
// 		res.x /= res.w;
// 		res.y /= res.w;
// 		res.z /= res.w;
// 	}
// 	return (res);
// }
