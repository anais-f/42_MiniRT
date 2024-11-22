#include "miniRT.h"

int	parse_sphere(char **line_parsed, t_minirt *minirt)
{
	if (arr_len(line_parsed) != 4)
	{
		printf("Sphere must have only three parameters\n");
		return (2);
	}
	parse_coordinates(line_parsed[1], &minirt->objects->position); // checker retour d'erreur si != 0 free & exit
	parse_color(line_parsed[3], &minirt->objects->color); // checker retour d'erreur parsing color si != 0 free & exit
	minirt->objects->type = SPHERE;
	if (is_valid_float(line_parsed[2]) == false)
		return (3);
	minirt->objects->spec.sphere.radius = (double)ft_atof(line_parsed[2]) / 2.f;
	printf("Sphere pos : %f %f %f diam : %f color %d %d %d\n", minirt->objects->position.x, minirt->objects->position.y, minirt->objects->position.z, minirt->objects->spec.sphere.radius, minirt->objects->color.r, minirt->objects->color.g, minirt->objects->color.b);
	return (0);
}

int	parse_plane(char **line_parsed, t_minirt *minirt)
{
	if (arr_len(line_parsed) != 4)
	{
		printf("Plane must have only three parameters\n");
		return (2);
	}
	parse_coordinates(line_parsed[1], &minirt->objects->position); // checker retour d'erreur si != 0 free & exit
	parse_coordinates(line_parsed[2], &minirt->objects->direction); // checker retour d'erreur si != 0 free & exit
	parse_color(line_parsed[3], &minirt->objects->color); // checker retour d'erreur parsing color si != 0 free & exit
	minirt->objects->type = PLANE;
	if (is_in_range(minirt->objects->direction.x, -1, 1) == false || \
		is_in_range(minirt->objects->direction.y, -1, 1) == false || \
		is_in_range(minirt->objects->direction.z, -1, 1) == false)
	{
		printf("Plane direction out of range\n");
		return (3);
	}
	printf("Plane pos : %f %f %f diam : %f color %d %d %d\n", minirt->objects->position.x, minirt->objects->position.y, minirt->objects->position.z, minirt->objects->spec.sphere.radius, minirt->objects->color.r, minirt->objects->color.g, minirt->objects->color.b);
	return (0);
}

int	parse_cylinder(char **line_parsed, t_minirt *minirt)
{
	if (arr_len(line_parsed) != 6)
	{
		printf("Cylinder must have only five parameters\n");
		return (2);
	}
	parse_coordinates(line_parsed[1], &minirt->objects->position); // checker retour d'erreur si != 0 free & exit
	parse_coordinates(line_parsed[2], &minirt->objects->direction); // checker retour d'erreur si != 0 free & exit
	parse_color(line_parsed[5], &minirt->objects->color); // checker retour d'erreur parsing color si != 0 free & exit
	minirt->objects->type = CYLINDER;
	if (is_in_range(minirt->objects->direction.x, -1, 1) == false || \
		is_in_range(minirt->objects->direction.y, -1, 1) == false || \
		is_in_range(minirt->objects->direction.z, -1, 1) == false)
	{
		printf("Cylinder direction out of range\n");
		return (3);
	}
	if (is_valid_float(line_parsed[3]) == false || is_valid_float(line_parsed[4]) == false)
	{
		printf("Cylinder radius or height is not a valid float\n");
		return (4);
	}
	minirt->objects->spec.cylinder.radius = (double)ft_atof(line_parsed[3]) / 2.0f;
	minirt->objects->spec.cylinder.height = (double)ft_atof(line_parsed[4]);
	printf("Cylinder pos : %f %f %f diam : %f height : %f color %d %d %d\n", minirt->objects->position.x, minirt->objects->position.y, minirt->objects->position.z, minirt->objects->spec.cylinder.radius, minirt->objects->spec.cylinder.height, minirt->objects->color.r, minirt->objects->color.g, minirt->objects->color.b);
	return (0);
}
