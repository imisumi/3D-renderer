/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichiro <ichiro@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 16:29:17 by ichiro            #+#    #+#             */
/*   Updated: 2023/04/07 20:26:19 by ichiro           ###   ########.fr       */
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

t_vec3 vec3_rotate_x(t_vec3 v, float angle);
t_vec3 vec3_rotate_y(t_vec3 v, float angle);
t_vec3 vec3_rotate_z(t_vec3 v, float angle);

#endif
