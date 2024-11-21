#include "miniRT.h"

int	parse_camera(char **line_parsed, t_minirt *minirt)
{
	if (minirt->cam.is_init)
	{
		printf("Camera aleready set\n");
		return (1);
	}
	if (arr_len(line_parsed) != 4)
	{
		printf("Camera must have only three parameters\n");
		return (2);
	}
	parse_coordinates(line_parsed[1], &minirt->cam.position); // checker retour d'erreur si != 0 free & exit
	parse_coordinates(line_parsed[2], &minirt->cam.direction); // checker retour d'erreur si != 0 free & exit
	minirt->cam.FOV = ft_atof(line_parsed[3]);
	if (check_range_items(minirt, CAMERA))
	{
		printf("Camera parameters out of range\n");
		return (3);
	}
	minirt->cam.is_init = true;
	return (0);
}
