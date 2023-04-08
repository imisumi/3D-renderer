/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichiro <ichiro@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 16:29:17 by ichiro            #+#    #+#             */
/*   Updated: 2023/04/08 14:50:22 by ichiro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ARRAY_H
#define ARRAY_H

#define array_push(array, value)                                              \
	do {                                                                      \
	    (array) = array_hold((array), 1, sizeof(*(array)));                   \
	    (array)[array_length(array) - 1] = (value);                           \
	} while (0);

void* array_hold(void* array, int count, int item_size);
int array_length(void* array);
void array_free(void* array);

#endif
