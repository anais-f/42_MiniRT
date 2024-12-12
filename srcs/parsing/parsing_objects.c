#include "miniRT.h"

int	add_object(t_object object, t_array *array)
{
	t_object	*object_ptr;

	object_ptr = malloc(sizeof(t_object));
	if (!object_ptr)
		return (-1);
	ft_memcpy(object_ptr, &object, sizeof(t_object));
	if (array_add(object_ptr, array) == -1)
	{
		free(object_ptr);
		return (1);
	}
	return (0);
}

int	check_range_direction(t_object *object, int type)
{
	if (is_in_range(object->direction.x, -RANGE, RANGE) == false || \
		is_in_range(object->direction.y, -RANGE, RANGE) == false || \
		is_in_range(object->direction.z, -RANGE, RANGE) == false)
	{
		if (type == CYLINDER)
			printf("Error :\nCylinder direction out of range\n");
		else if (type == PLANE)
			printf("Error :\nPlane direction out of range\n");
		return (3);
	}
	object->direction = normalize_vec3(object->direction);
	return (0);
}

int	parse_sphere(char **line_parsed, t_minirt *minirt)
{
	t_object	object;

	if (arr_len(line_parsed) != 4)
	{
		printf("Error :\nSphere must have only three parameters\n");
		return (1);
	}
	if (parse_coordinates(line_parsed[1], &object.position) \
		|| parse_color(line_parsed[3], &object.color) \
		|| !is_valid_float(line_parsed[2]))
		return (2);
	object.type = SPHERE;
	object.spec.sphere.radius = (double)ft_atof(line_parsed[2]) / 2.f;
	if (object.spec.sphere.radius <= 0.f)
	{
		printf("Error :\nSphere radius must be positive\n");
		return (3);
	}
	if (add_object(object, &minirt->objects))
		return (4);
	return (0);
}

int	parse_plane(char **line_parsed, t_minirt *minirt)
{
	t_object	object;

	if (arr_len(line_parsed) != 4)
	{
		printf("Error :\nPlane must have only three parameters\n");
		return (1);
	}
	if (parse_coordinates(line_parsed[1], &object.position) || \
		parse_coordinates(line_parsed[2], &object.direction) || \
		parse_color(line_parsed[3], &object.color))
		return (2);
	object.type = PLANE;
	if (check_range_direction(&object, object.type))
		return (3);
	if (add_object(object, &minirt->objects))
		return (4);
	return (0);
}

int	parse_cylinder(char **line_parsed, t_minirt *minirt)
{
	t_object	object;

	if (arr_len(line_parsed) != 6)
	{
		printf("Error :\nCylinder must have only five parameters\n");
		return (1);
	}
	if (parse_coordinates(line_parsed[1], &object.position) || \
		parse_coordinates(line_parsed[2], &object.direction) || \
		parse_color(line_parsed[5], &object.color))
		return (2);
	object.type = CYLINDER;
	if (check_range_direction(&object, object.type))
		return (3);
	if (!is_valid_float(line_parsed[3]) || !is_valid_float(line_parsed[4]))
		return (printf("Error :\nCylinder radius or height is not \
a valid float\n"), 4);
	object.spec.cy.radius = (double)ft_atof(line_parsed[3]) / 2.0f;
	object.spec.cy.height = (double)ft_atof(line_parsed[4]);
	if (object.spec.cy.radius <= 0.f || object.spec.cy.height <= 0.f)
		return (printf("Error :\nCylinder radius or height must \
be positive\n"), 5);
	if (add_object(object, &minirt->objects))
		return (6);
	return (0);
}
