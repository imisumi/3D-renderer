/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triangle.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichiro <ichiro@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 16:29:17 by ichiro            #+#    #+#             */
/*   Updated: 2023/04/07 20:51:33 by ichiro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TRIANGLE_H
# define TRIANGLE_H

#include "renderer.h"
// #include "vector.h"

typedef struct s_face
{
	int	a;
	int	b;
	int	c;
}	t_face;

typedef struct s_triangle
{
	t_vec2	points[3];
}	t_triangle;


#endif