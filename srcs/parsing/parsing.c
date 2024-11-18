#include "miniRT.h"

int	prasing_map(t_minirt *minirt, char *file)
{
	int		map_file;
	char	*line;

	map_file = open(file, O_RDONLY);
	if (map_file == -1)
	{
		printf("Failed to open the map\n");
		return (-1);
	}
	line = get_next_line(map_file);
	while (line)
	{
		parse_line(line, minirt);
		// printf("%s", line);
		free(line);
		line = get_next_line(map_file);
	}
	free(line);
	close(map_file);
	return (0);
}

int	parse_line(char *line, t_minirt *minirt)
{
	char	**line_parsed;

	(void)minirt;
	line_parsed = ft_split_whitespace(line);
	if (!line_parsed)
		return (-1); //free line & exit
	if (!arr_len(line_parsed))
		return (1);
	if (ft_strncmp(line_parsed[0], "A", ft_strlen(line_parsed[0])) == 0)
		return (parse_ambient_light(line_parsed, minirt));
	else if (ft_strncmp(line_parsed[0], "C", ft_strlen(line_parsed[0])) == 0)
		return (parse_camera(line_parsed, minirt));
	else if (ft_strncmp(line_parsed[0], "L", ft_strlen(line_parsed[0])) == 0)
		return (parse_light(line_parsed, minirt));
	else if (ft_strncmp(line_parsed[0], "pl", ft_strlen(line_parsed[0])) == 0)
		printf("%s", line_parsed[0]);
	else if (ft_strncmp(line_parsed[0], "sp", ft_strlen(line_parsed[0])) == 0)
		return (parsing_sphere(line_parsed, minirt));
	else if (ft_strncmp(line_parsed[0], "cy", ft_strlen(line_parsed[0])) == 0)
		printf("%s", line_parsed[0]);
	else
	{
		printf("Error map, unrecognized line : %s\n", line_parsed[0]); // free & exit function here
		free(line);
		free(line_parsed);
		exit(EXIT_FAILURE);
	}
	free(line_parsed);
	return (0);
}

int	parse_coordinates(char *arg_parsed, t_vec3 *position)
{
	char	**args_coord;
	size_t	i;
	float	coord[3];

	args_coord = ft_split(arg_parsed, ',');
	if (!args_coord)
		return (-1);
	if (arr_len(args_coord) != 3)
	{
		printf("coordinates args must have only three parameters (XYZ)\n");
		free(args_coord);
		return (1);
	}
	i = 0;
	while (i <= 2)
	{
		if (is_valid_float(args_coord[i]) == false)
			return (1);
		coord[i] = ft_atof(args_coord[i]);
		i++;
	}
	position->x = coord[0];
	position->y = coord[1];
	position->z = coord[2];
	free(args_coord);
	return (0);
}

int	parse_color(char *arg_parsed, t_color *color)
{
	char	**args_color;
	int		colors_int[3];

	args_color = ft_split(arg_parsed, ',');
	if (!args_color)
		return (-1);
	if (arr_len(args_color) != 3)
	{
		printf("Color args must have only three parameters (RGB)\n");
		free(args_color);
		return (1);
	}
	if (convert_color(args_color, colors_int))
		return (2); //free & exit ?
	color->r = colors_int[0];
	color->g = colors_int[1];
	color->b = colors_int[2];
	free(args_color);
	return (0);
}


