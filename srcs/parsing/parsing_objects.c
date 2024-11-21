#include "miniRT.h"

int	parse_sphere(char **line_parsed, t_minirt *minirt)
{
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
	printf("Sphere pos : %f %f %f diam : %f color %d %d %d\n", minirt->object.position.x, minirt->object.position.y, minirt->object.position.z, minirt->object.spec.sphere.radius, minirt->object.color.r, minirt->object.color.g, minirt->object.color.b);
	return (0);
}

int	parse_plane(char **line_parsed, t_minirt *minirt)
{
	if (arr_len(line_parsed) != 4)
	{
		printf("Plane must have only three parameters\n");
		return (2);
	}
	parse_coordinates(line_parsed[1], &minirt->object.position); // checker retour d'erreur si != 0 free & exit
	parse_coordinates(line_parsed[2], &minirt->object.direction); // checker retour d'erreur si != 0 free & exit
	parse_color(line_parsed[3], &minirt->object.color); // checker retour d'erreur parsing color si != 0 free & exit
	minirt->object.type = PLANE;
	if (is_in_range(minirt->object.direction.x, -1, 1) == false || \
		is_in_range(minirt->object.direction.y, -1, 1) == false || \
		is_in_range(minirt->object.direction.z, -1, 1) == false)
	{
		printf("Plane direction out of range\n");
		return (3);
	}
	printf("Plane pos : %f %f %f diam : %f color %d %d %d\n", minirt->object.position.x, minirt->object.position.y, minirt->object.position.z, minirt->object.spec.sphere.radius, minirt->object.color.r, minirt->object.color.g, minirt->object.color.b);
	return (0);
}

int	parse_cylinder(char **line_parsed, t_minirt *minirt)
{
	if (arr_len(line_parsed) != 6)
	{
		printf("Cylinder must have only five parameters\n");
		return (2);
	}
	parse_coordinates(line_parsed[1], &minirt->object.position); // checker retour d'erreur si != 0 free & exit
	parse_coordinates(line_parsed[2], &minirt->object.direction); // checker retour d'erreur si != 0 free & exit
	parse_color(line_parsed[5], &minirt->object.color); // checker retour d'erreur parsing color si != 0 free & exit
	minirt->object.type = CYLINDER;
	if (is_in_range(minirt->object.direction.x, -1, 1) == false || \
		is_in_range(minirt->object.direction.y, -1, 1) == false || \
		is_in_range(minirt->object.direction.z, -1, 1) == false)
	{
		printf("Cylinder direction out of range\n");
		return (3);
	}
	if (is_valid_float(line_parsed[3]) == false || is_valid_float(line_parsed[4]) == false)
	{
		printf("Cylinder radius or height is not a valid float\n");
		return (4);
	}
	minirt->object.spec.cylinder.radius = ft_atof(line_parsed[3]);
	minirt->object.spec.cylinder.height = ft_atof(line_parsed[4]);
	printf("Cylinder pos : %f %f %f diam : %f height : %f color %d %d %d\n", minirt->object.position.x, minirt->object.position.y, minirt->object.position.z, minirt->object.spec.cylinder.radius, minirt->object.spec.cylinder.height, minirt->object.color.r, minirt->object.color.g, minirt->object.color.b);
	return (0);
}
