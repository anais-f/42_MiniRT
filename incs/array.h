#ifndef ARRAY_H
# define ARRAY_H

#include "objects.h"

#define INIT_SIZE 4

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