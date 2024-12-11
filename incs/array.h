/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acancel <acancel@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 16:29:14 by acancel           #+#    #+#             */
/*   Updated: 2024/12/11 16:29:15 by acancel          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef ARRAY_H
# define ARRAY_H

# include "objects.h"
# include <stdio.h> // est ce qu'on garde les fonctions de print dans le push mandatory ?
# define INIT_SIZE 4

typedef struct s_array
{
	t_object	**array;
	size_t		allocated_size;
	size_t		size;
}	t_array;

void	array_init(t_array *array);
int		array_add(t_object *object, t_array *array);
void	array_free(t_array *array);
void	array_print(t_array array);

#endif