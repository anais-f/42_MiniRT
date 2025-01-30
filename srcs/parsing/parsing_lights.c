/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_lights.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anfichet <anfichet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 15:20:40 by acancel           #+#    #+#             */
/*   Updated: 2024/12/12 15:16:25 by anfichet         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	parse_ambient_light(char **line_parsed, t_minirt *minirt)
{
	if (minirt->ambient_light.is_init)
	{
		printf("Error :\nAmbient light already set\n");
		return (1);
	}
	if (arr_len(line_parsed) != 3)
	{
		printf("Error :\nAmbient light must have only three parameters\n");
		return (2);
	}
	if (parse_color(line_parsed[2], &minirt->ambient_light.color) \
		|| !is_valid_float(line_parsed[1]))
		return (3);
	minirt->ambient_light.brightness = (double)ft_atof(line_parsed[1]);
	if (check_range_items(minirt, AMBIENT_LIGHT))
	{
		printf("Error :\nAmbient light parameters out of range\n");
		return (4);
	}
	minirt->ambient_light.is_init = true;
	return (0);
}

int	parse_light(char **line_parsed, t_minirt *minirt)
{
	if (minirt->light.is_init)
	{
		printf("Error :\nAmbient light aleready set\n");
		return (1);
	}
	if (arr_len(line_parsed) != 4)
	{
		printf("Error :\nLight must have only three parameters\n");
		return (2);
	}
	if (parse_coordinates(line_parsed[1], &minirt->light.position) || \
			parse_color(line_parsed[3], &minirt->light.color) || \
			is_valid_float(line_parsed[2]) == false)
		return (3);
	minirt->light.brightness = (double)ft_atof(line_parsed[2]);
	if (check_range_items(minirt, LIGHT))
	{
		printf("Error :\nLight parameters out of range\n");
		return (4);
	}
	minirt->light.is_init = true;
	return (0);
}
