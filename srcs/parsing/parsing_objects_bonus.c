#include "miniRT.h"

int	parse_ellipsoid(char **line_parsed, t_minirt *minirt)
{
	t_object	object;

	if (arr_len(line_parsed) != 6)
	{
		printf("Ellipsoid must have only five parameters\n");
		return (1);
	}
	if (parse_coordinates(line_parsed[1], &object.position) \
		|| parse_color(minirt, line_parsed[5], &object.color) \
		|| !is_valid_float(line_parsed[2]) || !is_valid_float(line_parsed[3]) \
		|| !is_valid_float(line_parsed[4]))
		return (2);
	object.type = ELLIPSOID;
	object.spec.el.radius.x = (double)ft_atof(line_parsed[2]) / 2.f;
	object.spec.el.radius.y = (double)ft_atof(line_parsed[3]) / 2.f;
	object.spec.el.radius.z = (double)ft_atof(line_parsed[4]) / 2.f;
	if (add_object(object, &minirt->objects))
		return (3);
	return (0);
}
