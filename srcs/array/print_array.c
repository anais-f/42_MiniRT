#include "array.h"

void	print_obj_cylinder(t_array array, size_t i)
{
	printf("object[%ld]_CYLINDER : type %d, pos %f,%f,%f, \
	dir norm. %f,%f,%f, rad :%f, height :%f, color : %hhu,%hhu,%hhu\n", \
	i, array.array[i]->type, array.array[i]->position.x, \
	array.array[i]->position.y, array.array[i]->position.z, \
	array.array[i]->direction.x, array.array[i]->direction.y, \
	array.array[i]->direction.z, array.array[i]->spec.cylinder.radius, \
	array.array[i]->spec.cylinder.height, \
	array.array[i]->color.r, array.array[i]->color.g, \
	array.array[i]->color.b);
}

void	print_obj_plane(t_array array, size_t i)
{
	printf("object[%ld]_PLANE : type %d, pos %f,%f,%f," \
	"dir norm. %f,%f,%f, color : %hhu,%hhu,%hhu\n", i, \
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
