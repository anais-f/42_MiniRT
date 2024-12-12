/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_lights.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acancel <acancel@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 16:37:33 by acancel           #+#    #+#             */
/*   Updated: 2024/12/12 16:37:34 by acancel          ###   ########lyon.fr   */
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

int	parse_lights(char **line_parsed, t_minirt *minirt)
{
	t_object	light;

	if (arr_len(line_parsed) != 4)
	{
		printf("Error :\nLight must have only three parameters\n");
		return (1);
	}
	if (parse_coordinates(line_parsed[1], &light.position) || \
			parse_color(line_parsed[3], &light.color) || \
			is_valid_float(line_parsed[2]) == false)
		return (2);
	light.spec.light.brightness = (double)ft_atof(line_parsed[2]);
	if (light.spec.light.brightness < 0.f || light.spec.light.brightness > 1.f)
		return (3);
	if (add_object(light, &minirt->lights))
		return (4);
	return (0);
}
