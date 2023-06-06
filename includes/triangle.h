/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triangle.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichiro <ichiro@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 16:29:17 by ichiro            #+#    #+#             */
/*   Updated: 2023/06/04 17:17:06 by ichiro           ###   ########.fr       */
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
	color_t	color;
}	t_face;

typedef struct s_triangle
{
	t_vec2	points[3];
	color_t	color;
	float 	avg_depth;
}	t_triangle;

void	draw_filled_triangle(int x0, int y0, int x1, int y1, int x2, int y2, uint32_t color);
void	fill_flat_bottom(int x0, int y0, int x1, int y1, int x2, int y2, uint32_t color);
void	fill_flat_top(int x0, int y0, int x1, int y1, int x2, int y2, uint32_t color);

#endif