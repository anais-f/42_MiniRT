/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acancel <acancel@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 15:20:09 by acancel           #+#    #+#             */
/*   Updated: 2024/12/11 15:20:10 by acancel          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "array.h"
#include "libft.h"

static int	array_extend(t_array *array)
{
	t_object	**new_array;

	array->allocated_size *= 2;
	if (array->allocated_size == 0)
		array->allocated_size = INIT_SIZE;
	new_array = malloc(sizeof(t_object *) * array->allocated_size);
	if (!new_array)
		return (-1);
	ft_memcpy(new_array, array->array, array->size * sizeof(t_object *));
	free(array->array);
	array->array = new_array;
	return (0);
}

void	array_init(t_array *array)
{
	array->array = NULL;
	array->allocated_size = 0;
	array->size = 0;
}

int	array_add(t_object *object, t_array *array)
{
	if (array->allocated_size == array->size && array_extend(array) == -1)
		return (-1);
	array->array[array->size++] = object;
	return (0);
}

void	array_free(t_array *array)
{
	size_t	i;

	i = 0;
	while (i < array->size)
		free(array->array[i++]);
	free(array->array);
	array_init(array);
}
