#include "miniRT.h"

static int	add_object(t_object object, t_minirt *minirt)
{
	t_object	*object_ptr;

	object_ptr = malloc(sizeof(t_object));
	if (!object_ptr)
		return (-1);
	ft_memcpy(object_ptr, &object, sizeof(t_object));
	if (array_add(object_ptr, &minirt->objects) == -1)
	{
		free(object_ptr);
		return (1);
	}
	return (0);
}

int	check_range_direction(t_object object, int type)
{
	if (is_in_range(object.direction.x, -1, 1) == false || \
		is_in_range(object.direction.y, -1, 1) == false || \
		is_in_range(object.direction.z, -1, 1) == false)
	{
		if (type == CYLINDER)
			printf("Cylinder direction out of range\n");
		else if (type == PLANE)
			printf("Plane direction out of range\n");
		return (3);
	}
	return (0);
}

int	parse_sphere(char **line_parsed, t_minirt *minirt)
{
	t_object	object;

	if (arr_len(line_parsed) != 4)
	{
		printf("Sphere must have only three parameters\n");
		return (1);
	}
	if (parse_coordinates(line_parsed[1], &object.position) \
		|| parse_color(minirt, line_parsed[3], &object.color) \
		|| !is_valid_float(line_parsed[2]))
		return (2);
	object.type = SPHERE;
	object.spec.sphere.radius = (double)ft_atof(line_parsed[2]) / 2.f;
	if (add_object(object, minirt))
		return (3);
	return (0);
}

int	parse_plane(char **line_parsed, t_minirt *minirt)
{
	t_object	object;

	if (arr_len(line_parsed) != 4)
	{
		printf("Plane must have only three parameters\n");
		return (1);
	}
	if (parse_coordinates(line_parsed[1], &object.position) || \
		parse_coordinates(line_parsed[2], &object.direction) || \
		parse_color(minirt, line_parsed[3], &object.color))
		return (2);
	object.type = PLANE;
	if (check_range_direction(object, object.type))
		return (3);
	if (add_object(object, minirt))
		return (4);
	return (0);
}

int	parse_cylinder(char **line_parsed, t_minirt *minirt)
{
	t_object	object;

	if (arr_len(line_parsed) != 6)
	{
		printf("Cylinder must have only five parameters\n");
		return (1);
	}
	if (parse_coordinates(line_parsed[1], &object.position) || \
		parse_coordinates(line_parsed[2], &object.direction) || \
		parse_color(minirt, line_parsed[5], &object.color))
		return (2);
	object.type = CYLINDER;
	if (check_range_direction(object, object.type))
		return (3);
	if (!is_valid_float(line_parsed[3]) || !is_valid_float(line_parsed[4]))
	{
		printf("Cylinder radius or height is not a valid float\n");
		return (4);
	}
	object.spec.cylinder.radius = (double)ft_atof(line_parsed[3]) / 2.0f;
	object.spec.cylinder.height = (double)ft_atof(line_parsed[4]);
	if (add_object(object, minirt))
		return (5);
	return (0);
}

//printf("Plane pos : %f %f %f direction : %f %f %f color %d %d %d\n", object->position.x, object->position.y, object->position.z, object->direction.x, object->direction.y, object->direction.z, object->color.r, object->color.g, object->color.b);
//printf("Cylinder pos : %f %f %f diam : %f height : %f color %d %d %d\n", object.position.x, object.position.y, object.position.z, object.spec.cylinder.radius, object.spec.cylinder.height, object.color.r, object.color.g, object.color.b);
