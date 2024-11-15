#include "miniRT.h"

bool	is_valid_float(char *str_float);
char	*ft_iswspace(char *str);
float	ft_atof(const char *str);
int		pars_ambient_light(char **line_parsed, t_minirt *minirt);
int		pars_camera(char **line_parsed, t_minirt *minirt);
int		pars_color(char *arg_parsed, t_color *color);
int		pars_coordinates(char *arg_parsed, t_vec3 *position);
int		pars_line(char *line, t_minirt *minirt);
size_t	arr_len(char **arr);
void	ft_free_arr(char **arr);
void	print_arr(char **arr);


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
		pars_line(line, minirt);
		// printf("%s", line);
		free(line);
		line = get_next_line(map_file);
	}
	free(line);
	close(map_file);
	return (0);
}

int	pars_line(char *line, t_minirt *minirt)
{
	char	**line_parsed;

	(void)minirt;
	line_parsed = ft_split_whitespace(line);
	if (!line_parsed)
		return (-1); //free line & exit
	if (!arr_len(line_parsed))
		return (1);
	if (ft_strncmp(line_parsed[0], "A", ft_strlen(line_parsed[0])) == 0)
		return (pars_ambient_light(line_parsed, minirt));
	else if (ft_strncmp(line_parsed[0], "C", ft_strlen(line_parsed[0])) == 0)
		return (pars_camera(line_parsed, minirt));
	else if (ft_strncmp(line_parsed[0], "L", ft_strlen(line_parsed[0])) == 0)
		printf("%s", line_parsed[0]);
	else if (ft_strncmp(line_parsed[0], "pl", ft_strlen(line_parsed[0])) == 0)
		printf("%s", line_parsed[0]);
	else if (ft_strncmp(line_parsed[0], "sp", ft_strlen(line_parsed[0])) == 0)
		printf("%s", line_parsed[0]);
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

int	pars_camera(char **line_parsed, t_minirt *minirt)
{
	if (minirt->cam.is_init)
	{
		printf("Camera aleready set\n");
		return (1);
	}
	if (arr_len(line_parsed) != 4)
	{
		printf("Camera must have only three parameters\n");
		return (2);
	}
	pars_coordinates(line_parsed[1], &minirt->cam.position); // checker retour d'erreur parsing color si != 0 free & exit
	minirt->cam.is_init = true;
	return (0);
}

int	pars_coordinates(char *arg_parsed, t_vec3 *position)
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

int	pars_ambient_light(char **line_parsed, t_minirt *minirt)
{
	float	brightness;
	if (minirt->ambient_light.is_init)
	{
		printf("Ambient light aleready set\n");
		return (1);
	}
	if (arr_len(line_parsed) != 3)
	{
		printf("Ambient light must have only three parameters\n");
		return (2);
	}
	pars_color(line_parsed[2], &minirt->ambient_light.color); // checker retour d'erreur parsing color si != 0 free & exit
	if (is_valid_float(line_parsed[1]) == false)
		return (3);
	brightness = ft_atof(line_parsed[1]);
	if (brightness < 0 || brightness > 1)
		return (printf("Brightness of Ambient line must be defined between 0 and 1\n"), 4);
	minirt->ambient_light.brightness = brightness;
	minirt->ambient_light.is_init = true;
	return (0);
}
/*Print colors and brightness for debug Ambient light pars only*/
	// printf("r = %i\n", minirt->ambient_light.color.r);
	// printf("g = %i\n", minirt->ambient_light.color.g);
	// printf("b = %i\n", minirt->ambient_light.color.b);
	//printf("A brightness = %f\n", minirt->ambient_light.brightness);

int	pars_color(char *arg_parsed, t_color *color)
{
	char	**args_color;
	size_t	i;
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
	i = 0;
	while (i <= 2)
	{
		colors_int[i] = ft_atoi(args_color[i]);
		if ((colors_int[i] == -1 || colors_int[i] > 255 ) && errno == ERANGE)
		{
			errno = 0;  //useless ? if errno != 0 free & exit so... ?
			printf("Color must be a value between 0 and 255\n");
			return (2);
		}
		i++;
	}
	color->r = colors_int[0];
	color->g = colors_int[1];
	color->b = colors_int[2];
	free(args_color);
	return (0);
}

bool	is_valid_float(char *str_float)
{
	int		i;
	bool	comma;

	i = 0;
	comma = false;
	if (str_float[i] == '+' || str_float[i] == '-')
		i++;
	if (str_float[i] == '.')
	{
		comma = true;
		i++;
	}
	while ((str_float[i] >= '0' && str_float[i] <= '9') || str_float[i] == '.')
	{
		if (str_float[i] == '.')
		{	
			if (comma == true)
				return (printf("Wrong float format %s\n", str_float), false);
			comma = true;
		}
		i++;
	}
	if (i != (int)ft_strlen(str_float))
		return (printf("Wrong float format %s\n", str_float), false);
	return (true);
}

char	*ft_iswspace(char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		if (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
			i++;
		else
			break ;
	}
	return (str + i);
}

void	print_arr(char **arr)
{
	int	i;

	i = -1;
	while (arr[++i])
		printf("%s\n", arr[i]);
	return ;
}

size_t	arr_len(char **arr)
{
	size_t	i;

	i = 0;
	while (arr[i])
		i++;
	return (i);
}

void	ft_free_arr(char **arr)
{
	int	i;

	i = -1;
	while (arr[++i])
		free(arr[i]);
	free(arr);
}

float	ft_atof(const char *str)
{
	size_t	i;
	float	nb_bf_comma;
	float	nb_af_comma;
	int		sign;

	i = 0;
	nb_bf_comma = 0.f;
	nb_af_comma = 0.0f;
	sign = 1;
	// while (str[i] == ' ' || (str[i] >= '\t' && str[i] <= '\r')) useless here aleready splited on WSpaces
	// 	i++;
	if (str[i] == '-')
		sign = -sign;
	if (str[i] == '+' || str[i] == '-')
		i++;
	while ((str[i] >= '0' && str[i] <= '9'))
	{
		if ((((int)nb_bf_comma * 10 + str[i] - '0') / 10) != (int)nb_bf_comma)
		{
			errno = ERANGE;
			if (sign < 0)
				return ((float)INT_MIN);
			return ((float)INT_MAX);
		}
		nb_bf_comma = nb_bf_comma * 10 + str[i++] - '0';
	}
	if (str[i] == '.')
	{
		i = ft_strlen(str) - 1;
		while ((str[i] >= '0' && str[i] <= '9'))
			nb_af_comma = nb_af_comma / 10 + str[i--] - '0';
	}
	return ((nb_bf_comma + nb_af_comma / 10) * sign);
}

// int	prasing_map(t_minirt *minirt, char *file) 
//t_minirt *minirt a passer afin d'initialiser les struct avec les infos de la map
// {
// 	int		map_file;
// 	char	**pars_line;
// 	int		i;
// 	char	**pars_arg;
// 	int		fov_pars;
// 	char	*s;

// 	i = 0;
// 	fov_pars = 0.f;
// 	map_file = open(file, O_RDONLY);
// 	if (map_file == -1)
// 	{
// 		printf("Failed to open the map\n");
// 		return (-1);
// 	}
// 	s = get_next_line(map_file);
// 	while (s != NULL)
// 	{
// 		free(s);
// 		s = get_next_line(map_file);
// 		i++;
// 	}
// 	printf("nb line %d = 6\n", i);
// 	close(map_file);

// 	pars_line = malloc(sizeof(char *) * (i + 1));
// 	if (pars_line == NULL)
// 	{
// 		printf("Malloc filed\n");
// 		return (-1);
// 	}
	
// 	i = 0;
// 	map_file = open(file, O_RDONLY);
// 	if (map_file == -1)
// 	{
// 		printf("Failed to open the map\n");
// 		return (-1);
// 	}
// 	pars_line[i] = get_next_line(map_file);
// 	while (pars_line[i] != NULL)
// 	{
// 		printf("line %d : %s", i, pars_line[i]);
// 		i++;
// 		pars_line[i] = get_next_line(map_file);
// 	}
// 	pars_arg = ft_split(pars_line[1], ' ');
// 	print_arr(pars_arg);
// 	printf("FOV bf atoi: %s\n", pars_arg[3]);
// 	fov_pars = ft_atoi(pars_arg[3]);
// 	minirt->cam.FOV = (float)fov_pars; //normalement fov pars
// 	printf("fov : %f\n", minirt->cam.FOV);
// 	close(map_file);
// 	ft_free_arr(pars_arg);
// 	ft_free_arr(pars_line);
// 	return (0);
// }