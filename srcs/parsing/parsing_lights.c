#include "miniRT.h"

int	parse_ambient_light(char **line_parsed, t_minirt *minirt)
{
	if (minirt->ambient_light.is_init)
	{
		printf("Ambient light aleready set\n");
		ft_free_exit(minirt, NULL, line_parsed, 1);
	}
	if (arr_len(line_parsed) != 3)
	{
		printf("Ambient light must have only three parameters\n");
		return (2);
	}
	if (parse_color(minirt, line_parsed[2], &minirt->ambient_light.color) || is_valid_float(line_parsed[1]) == false)
		return (1);
	minirt->ambient_light.brightness = (double)ft_atof(line_parsed[1]);
	if (check_range_items(minirt, AMBIENT_LIGHT))
	{
		printf("Ambient light parameters out of range\n");
		ft_free_exit(minirt, NULL, line_parsed, 4);
	}
	minirt->ambient_light.is_init = true;
	return (0);
}

int	parse_light(char **line_parsed, t_minirt *minirt)
{
	if (minirt->light.is_init)
	{
		printf("Ambient light aleready set\n");
		return (1);
	}
	if (arr_len(line_parsed) != 4)
	{
		printf("Light must have only three parameters\n");
		return (2);
	}
	if (parse_coordinates(line_parsed[1], &minirt->light.position) || \
			parse_color(minirt, line_parsed[3], &minirt->light.color) || \
			is_valid_float(line_parsed[2]) == false)
		return (3);
	minirt->light.brightness = (double)ft_atof(line_parsed[2]);
	if (check_range_items(minirt, LIGHT))
	{
		printf("Light parameters out of range\n");
		return (4);
	}
	minirt->light.is_init = true;
	return (0);
}
