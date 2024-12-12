/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acancel <acancel@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 16:37:18 by acancel           #+#    #+#             */
/*   Updated: 2024/12/12 16:37:19 by acancel          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	check_argv(int argc, char *str)
{
	const char	str_check[] = ".rt";
	size_t		len_str;

	if (argc != 2)
	{
		printf("Error :\nInvalid number of arguments\n");
		return (1);
	}
	len_str = ft_strlen(str);
	if (len_str < 4)
	{
		printf("Error :\nInvalid parameter\n");
		return (1);
	}
	if (ft_strncmp(str_check, &str[len_str - 3], 4) != 0)
	{
		printf("Error :\nInvalid file\n");
		return (1);
	}
	return (0);
}

int	fill_coord(char **args_coord, float *coord)
{
	size_t	i;

	i = 0;
	while (i <= 2)
	{
		if (is_valid_float(args_coord[i]) == false)
			return (1);
		coord[i] = ft_atof(args_coord[i]);
		if (errno == ERANGE)
		{
			errno = 0;
			printf("Error :\nOverflow detected\n");
			return (1);
		}
		i++;
	}
	return (0);
}

int	parse_coordinates(char *arg_parsed, t_vec3 *position)
{
	char	**args_coord;
	float	coord[3];

	args_coord = split_commas(arg_parsed, ',');
	if (!args_coord)
		return (-1);
	if (arr_len(args_coord) != 3)
	{
		printf("Error :\ncoordinates args must have only \
three parameters (XYZ)\n");
		ft_free_arr(args_coord);
		return (1);
	}
	if (fill_coord(args_coord, coord))
	{
		ft_free_arr(args_coord);
		return (2);
	}
	position->x = coord[0];
	position->y = coord[1];
	position->z = coord[2];
	ft_free_arr(args_coord);
	return (0);
}

int	parse_color(char *arg_parsed, t_color *color)
{
	char	**args_color;
	int		colors_int[3];

	args_color = split_commas(arg_parsed, ',');
	if (!args_color)
		return (-1);
	if (arr_len(args_color) != 3)
	{
		printf("Error :\nColor args must \
have only three parameters (RGB)\n");
		ft_free_arr(args_color);
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
