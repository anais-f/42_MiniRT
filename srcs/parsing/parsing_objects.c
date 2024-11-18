#include "miniRT.h"

int	parsing_sphere(char **line_parsed, t_minirt *minirt)
{
	if (minirt->object.is_init)
	{
		printf("Object already set\n");
		return (1);
	}
	if (arr_len(line_parsed) != 4)
	{
		printf("Sphere must have only three parameters\n");
		return (2);
	}
	parse_coordinates(line_parsed[1], &minirt->object.position); // checker retour d'erreur si != 0 free & exit
	parse_color(line_parsed[3], &minirt->object.color); // checker retour d'erreur parsing color si != 0 free & exit
	minirt->object.type = SPHERE;
	if (is_valid_float(line_parsed[2]) == false)
		return (3);
	minirt->object.spec.sphere.radius = ft_atof(line_parsed[2]);
	minirt->object.is_init = true;
	printf("Sphere pos : %f %f %f diam : %f color %d %d %d\n", minirt->object.position.x, minirt->object.position.y, minirt->object.position.z, minirt->object.spec.sphere.radius, minirt->object.color.r, minirt->object.color.g, minirt->object.color.b);
	return (0);
}
