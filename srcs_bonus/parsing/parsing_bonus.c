/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acancel <acancel@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 16:37:25 by acancel           #+#    #+#             */
/*   Updated: 2025/01/29 13:27:58 by acancel          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT_bonus.h"

static bool	is_all_init(t_minirt *minirt)
{
	if (minirt->ambient_light.is_init && minirt->cam.is_init && \
		minirt->lights.size > 0)
		return (true);
	printf("Error :\nMissing A, C or L\n");
	return (false);
}

static int	check_direction(t_minirt minirt)
{
	size_t	i;

	i = 0;
	while (i < minirt.objects.size)
	{
		if (minirt.objects.array[i]->type == PLANE || \
			minirt.objects.array[i]->type == CYLINDER)
		{
			if (isnan(minirt.objects.array[i]->direction.x))
			{
				printf("Error :\nDirection of object[%ld] \
can't be normalized\n", i);
				return (1);
			}
		}
		i++;
	}
	return (0);
}

static int	select_parser(char **line_parsed, t_minirt *minirt)
{
	if (ft_strncmp(line_parsed[0], "A", ft_strlen(line_parsed[0])) == 0)
		return (parse_ambient_light(line_parsed, minirt));
	else if (ft_strncmp(line_parsed[0], "C", ft_strlen(line_parsed[0])) == 0)
		return (parse_camera(line_parsed, minirt));
	else if (ft_strncmp(line_parsed[0], "L", ft_strlen(line_parsed[0])) == 0)
		return (parse_lights(line_parsed, minirt));
	else if (ft_strncmp(line_parsed[0], "pl", ft_strlen(line_parsed[0])) == 0)
		return (parse_plane(line_parsed, minirt));
	else if (ft_strncmp(line_parsed[0], "sp", ft_strlen(line_parsed[0])) == 0)
		return (parse_sphere(line_parsed, minirt));
	else if (ft_strncmp(line_parsed[0], "cy", ft_strlen(line_parsed[0])) == 0)
		return (parse_cylinder(line_parsed, minirt));
	else if (ft_strncmp(line_parsed[0], "#", ft_strlen(line_parsed[0])) == 0)
		return (0);
	else if (ft_strncmp(line_parsed[0], "el", ft_strlen(line_parsed[0])) == 0)
		return (parse_ellipsoid(line_parsed, minirt));
	return (-1);
}

int	parsing_map(t_minirt *minirt, char *file)
{
	int		map_file;
	char	*line;

	map_file = open(file, O_RDONLY);
	if (map_file == -1)
	{
		printf("Error :\nFailed to open the map\n");
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
	if (check_direction(*minirt) || !is_all_init(minirt))
		return (1);
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
