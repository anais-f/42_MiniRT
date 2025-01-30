/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_array_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acancel <acancel@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 16:37:52 by acancel           #+#    #+#             */
/*   Updated: 2025/01/29 13:26:39 by acancel          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "array_bonus.h"

void	print_obj_cylinder(t_array array, size_t i)
{
	printf("object[%ld]_CYLINDER : type %d, pos %f,%f,%f, \
dir norm. %f,%f,%f, rad : %f, height : %f, color : %hhu,%hhu,%hhu\n", \
	i, array.array[i]->type, array.array[i]->position.x, \
	array.array[i]->position.y, array.array[i]->position.z, \
	array.array[i]->direction.x, array.array[i]->direction.y, \
	array.array[i]->direction.z, array.array[i]->spec.cy.radius, \
	array.array[i]->spec.cy.height, \
	array.array[i]->color.r, array.array[i]->color.g, \
	array.array[i]->color.b);
}

void	print_obj_plane(t_array array, size_t i)
{
	printf("object[%ld]_PLANE : type %d, pos %f,%f,%f, \
dir norm. %f,%f,%f, color : %hhu,%hhu,%hhu\n", i, \
	array.array[i]->type, array.array[i]->position.x, \
	array.array[i]->position.y, array.array[i]->position.z, \
	array.array[i]->direction.x, array.array[i]->direction.y, \
	array.array[i]->direction.z, array.array[i]->color.r, \
	array.array[i]->color.g, array.array[i]->color.b);
}

void	print_obj_sphere(t_array array, size_t i)
{
	printf("object[%ld]_SPHERE : type %d, pos %f,%f,%f, rad : %f," \
		" color : %hhu,%hhu,%hhu\n", i, array.array[i]->type, \
		array.array[i]->position.x, array.array[i]->position.y, \
		array.array[i]->position.z, array.array[i]->spec.sphere.radius, \
		array.array[i]->color.r, array.array[i]->color.g, \
		array.array[i]->color.b);
}

void	array_print(t_array array)
{
	size_t	i;

	i = 0;
	while (i < array.size)
	{
		if (array.array[i]->type == SPHERE)
			print_obj_sphere(array, i);
		else if (array.array[i]->type == PLANE)
			print_obj_plane(array, i);
		else if (array.array[i]->type == CYLINDER)
			print_obj_cylinder(array, i);
		i++;
	}
}

void	lights_print(t_array lights)
{
	size_t	i;

	i = 0;
	while (i < lights.size)
	{
		printf("Light[%zu] pos : %f, %f, %f brightness : %f\n", i, \
		lights.array[i]->position.x, lights.array[i]->position.y, \
		lights.array[i]->position.z, lights.array[i]->spec.light.brightness);
		i++;
	}
}
