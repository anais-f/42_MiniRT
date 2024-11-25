#include "miniRT.h"

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

int	convert_color(char **args_color, int *colors_int)
{
	size_t	i;

	i = 0;
	while (i <= 2)
	{
		colors_int[i] = ft_atoi(args_color[i]);
		if ((colors_int[i] == -1 || colors_int[i] > 255) || errno == ERANGE)
		{
			errno = 0;
			printf("Color must be a value between 0 and 255\n");
			return (1);
		}
		i++;
	}
	return (0);
}

bool	is_in_range(float value, float min, float max)
{
	if (value < min || value > max)
	{
		printf("value : %f min : %f max : %f\n", value, min, max);
		return (false);
	}
	return (true);
}

bool	check_range_items(t_minirt *minirt, t_items items)
{
	if (items == AMBIENT_LIGHT)
	{
		if (!is_in_range(minirt->ambient_light.brightness, 0.f, 1.f) || \
			!is_in_range(minirt->ambient_light.color.r, 0, 255) || \
			!is_in_range(minirt->ambient_light.color.g, 0, 255) || \
			!is_in_range(minirt->ambient_light.color.b, 0, 255))
			return (true);
	}
	if (items == CAMERA)
	{
		if (!is_in_range(minirt->cam.direction.x, -1, 1) || \
			!is_in_range(minirt->cam.direction.y, -1, 1) || \
			!is_in_range(minirt->cam.direction.z, -1, 1) || \
			!is_in_range(minirt->cam.FOV, 0, 180))
			return (true);
	}
	if (items == LIGHT)
	{
		if (!is_in_range(minirt->light.brightness, 0.f, 1.f) || \
			!is_in_range(minirt->light.color.r, 0, 255) || \
			!is_in_range(minirt->light.color.g, 0, 255) || \
			!is_in_range(minirt->light.color.b, 0, 255))
			return (true);
	}
	return (false);
}

void	print_parsing(t_minirt *minirt)
{
	size_t	i;

	i = 0;
	printf("ambient light brightness : %f clolor : %d %d %d\n",
		minirt->ambient_light.brightness, minirt->ambient_light.color.r,
		minirt->ambient_light.color.g, minirt->ambient_light.color.b);
	printf("camera pos : %f %f %f dir : %f %f %f fov : %f\n",
		minirt->cam.position.x, minirt->cam.position.y,
		minirt->cam.position.z, minirt->cam.direction.x,
		minirt->cam.direction.y, minirt->cam.direction.z,
		minirt->cam.FOV);
	printf("light pos : %f %f %f brightness : %f color : %d %d %d\n",
		minirt->light.position.x, minirt->light.position.y,
		minirt->light.position.z, minirt->light.brightness,
		minirt->light.color.r, minirt->light.color.g, minirt->light.color.b);
	array_print(minirt->objects);
}
