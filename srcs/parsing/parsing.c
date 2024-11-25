#include "miniRT.h"

static int	select_parser(char **line_parsed, t_minirt *minirt)
{
	if (ft_strncmp(line_parsed[0], "A", ft_strlen(line_parsed[0])) == 0)
		return (parse_ambient_light(line_parsed, minirt));
	else if (ft_strncmp(line_parsed[0], "C", ft_strlen(line_parsed[0])) == 0)
		return (parse_camera(line_parsed, minirt));
	else if (ft_strncmp(line_parsed[0], "L", ft_strlen(line_parsed[0])) == 0)
		return (parse_light(line_parsed, minirt));
	else if (ft_strncmp(line_parsed[0], "pl", ft_strlen(line_parsed[0])) == 0)
		return (parse_plane(line_parsed, minirt));
	else if (ft_strncmp(line_parsed[0], "sp", ft_strlen(line_parsed[0])) == 0)
		return (parse_sphere(line_parsed, minirt));
	else if (ft_strncmp(line_parsed[0], "cy", ft_strlen(line_parsed[0])) == 0)
		return (parse_cylinder(line_parsed, minirt));
	return (-1);
}

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
		free(line);
		line = get_next_line(map_file);
	}
	free(line);
	close(map_file);
	return (0);
}

void	parse_line(char *line, t_minirt *minirt)
{
	char	**line_parsed;

	line_parsed = ft_split_whitespace(line);
	if (!line_parsed)
		ft_free_exit(minirt, line, line_parsed, -1);
	if (!arr_len(line_parsed))
	{
		ft_free_arr(line_parsed);
		return ;
	}
	if (select_parser(line_parsed, minirt))
	{
		printf("Error map, on line : %s\n", line);
		ft_free_exit(minirt, line, line_parsed, 2);
	}
	ft_free_arr(line_parsed);
	return ;
}

int	parse_coordinates(char *arg_parsed, t_vec3 *position)
{
	char	**args_coord;
	size_t	i;
	float	coord[3];

	args_coord = split_comas(arg_parsed, ',');
	if (!args_coord)
		return (-1);
	if (arr_len(args_coord) != 3)
	{
		printf("coordinates args must have only three parameters (XYZ)\n");
		ft_free_arr(args_coord);
		return (1);
	}
	i = 0;
	while (i <= 2)
	{
		if (is_valid_float(args_coord[i]) == false)
		{
			ft_free_arr(args_coord);
			return (2);
		}
		coord[i] = ft_atof(args_coord[i]);
		i++;
	}
	position->x = coord[0];
	position->y = coord[1];
	position->z = coord[2];
	ft_free_arr(args_coord);
	return (0);
}

int	parse_color(t_minirt *minirt, char *arg_parsed, t_color *color)
{
	char	**args_color;
	int		colors_int[3];

	args_color = split_comas(arg_parsed, ',');
	if (!args_color)
		return (-1);
	if (arr_len(args_color) != 3)
	{
		printf("Color args must have only three parameters (RGB)\n");
		ft_free_exit(minirt, arg_parsed, args_color, 2);
		return (1);
	}
	if (convert_color(args_color, colors_int))
	{
		ft_free_arr(args_color);
		return (1);
	}
	color->r = colors_int[0];
	color->g = colors_int[1];
	color->b = colors_int[2];
	ft_free_arr(args_color);
	return (0);
}
