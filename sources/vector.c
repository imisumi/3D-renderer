/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichiro <ichiro@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 15:56:24 by ichiro            #+#    #+#             */
/*   Updated: 2023/04/07 17:35:19 by ichiro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/renderer.h"

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