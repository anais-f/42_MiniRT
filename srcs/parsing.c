#include "miniRT.h"

#include <sys/stat.h>
#include <fcntl.h>

void prasing_map(t_minirt *minirt, char *av)
{
	int map_file;

	map_file = open(av[1], O_RDONLY);
	if (map_file == -1)
	printf

}