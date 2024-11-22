#include "miniRT.h"

int	parse_sphere(char **line_parsed, t_minirt *minirt)
{
	t_object	*object;

	object = malloc(sizeof(t_object));
	if (!object)
		return (-1);
	if (arr_len(line_parsed) != 4)
	{
		printf("Sphere must have only three parameters\n");
		free(object);
		return (1);
	}
	if (parse_coordinates(line_parsed[1], &object->position) || parse_color(minirt, line_parsed[3], &object->color) || is_valid_float(line_parsed[2]) == false)
	{
		free(object);
		return (2);
	}
	object->type = SPHERE;
	object->spec.sphere.radius = (double)ft_atof(line_parsed[2]) / 2.f;
	if (array_add(object, &minirt->objects) == -1)
	{
		free(object);
		return(3);
	}
	printf("Sphere pos : %f %f %f diam : %f color %d %d %d\n", object->position.x, object->position.y, object->position.z, object->spec.sphere.radius, object->color.r, object->color.g, object->color.b);
	return (0);
}

int	parse_plane(char **line_parsed, t_minirt *minirt)
{
	t_object	*object;

	object = malloc(sizeof(t_object));
	if (!object)
		return (-1);
	if (arr_len(line_parsed) != 4)
	{
		printf("Plane must have only three parameters\n");
		free(object);
		return (1);
	}
	if (parse_coordinates(line_parsed[1], &object->position) || \
		parse_coordinates(line_parsed[2], &object->direction) || \
		parse_color(minirt, line_parsed[3], &object->color))
	{
		free(object);
		return (2);
	}
	object->type = PLANE;
	if (is_in_range(object->direction.x, -1, 1) == false || \
		is_in_range(object->direction.y, -1, 1) == false || \
		is_in_range(object->direction.z, -1, 1) == false)
	{
		printf("Plane direction out of range\n");
		free(object);
		return (3);
	}
	if (array_add(object, &minirt->objects) == -1)
	{
		free(object);
		ft_free_exit(minirt, NULL, line_parsed, -1);
	}
	printf("Plane pos : %f %f %f direction : %f %f %f color %d %d %d\n", object->position.x, object->position.y, object->position.z, object->direction.x, object->direction.y, object->direction.z, object->color.r, object->color.g, object->color.b);
	return (0);
}

int	parse_cylinder(char **line_parsed, t_minirt *minirt)
{
	t_object	*object;

	object = malloc(sizeof(t_object));
	if (!object)
		ft_free_exit(minirt, NULL, line_parsed, 1);
	if (arr_len(line_parsed) != 6)
	{
		printf("Cylinder must have only five parameters\n");
		ft_free_exit(minirt, NULL, line_parsed, 2);
	}
	parse_coordinates(line_parsed[1], &object->position); // checker retour d'erreur si != 0 free & exit
	parse_coordinates(line_parsed[2], &object->direction); // checker retour d'erreur si != 0 free & exit
	parse_color(minirt, line_parsed[5], &object->color); // checker retour d'erreur parsing color si != 0 free & exit
	object->type = CYLINDER;
	if (is_in_range(object->direction.x, -1, 1) == false || \
		is_in_range(object->direction.y, -1, 1) == false || \
		is_in_range(object->direction.z, -1, 1) == false)
	{
		printf("Cylinder direction out of range\n");
		ft_free_exit(minirt, NULL, line_parsed, 3);
	}
	if (is_valid_float(line_parsed[3]) == false || is_valid_float(line_parsed[4]) == false)
	{
		printf("Cylinder radius or height is not a valid float\n");
		ft_free_exit(minirt, NULL, line_parsed, 4);
	}
	object->spec.cylinder.radius = (double)ft_atof(line_parsed[3]) / 2.0f;
	object->spec.cylinder.height = (double)ft_atof(line_parsed[4]);
	if (array_add(object, &minirt->objects) == -1)
	{
		free(object);
		ft_free_exit(minirt, NULL, line_parsed, -1);
	}
	printf("Cylinder pos : %f %f %f diam : %f height : %f color %d %d %d\n", object->position.x, object->position.y, object->position.z, object->spec.cylinder.radius, object->spec.cylinder.height, object->color.r, object->color.g, object->color.b);
	return (0);
}
