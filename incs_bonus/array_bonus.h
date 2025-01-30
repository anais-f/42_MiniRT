/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acancel <acancel@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 16:35:15 by acancel           #+#    #+#             */
/*   Updated: 2025/01/29 13:29:24 by acancel          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef ARRAY_BONUS_H
# define ARRAY_BONUS_H

# include "objects_bonus.h"
# include <stdio.h>
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
void	lights_print(t_array lights);

#endif