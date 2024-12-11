/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_cam.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acancel <acancel@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 15:20:36 by acancel           #+#    #+#             */
/*   Updated: 2024/12/11 15:20:37 by acancel          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	parse_camera(char **line_parsed, t_minirt *minirt)
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
	if (parse_coordinates(line_parsed[1], &minirt->cam.position) || \
			parse_coordinates(line_parsed[2], &minirt->cam.direction) \
			|| errno == ERANGE)
	{
		printf("Error parsing camera coordinates\n");
		return (3);
	}
	minirt->cam.fov = ft_atof(line_parsed[3]);
	if (check_range_items(minirt, CAMERA))
	{
		printf("Camera parameters out of range\n");
		return (4);
	}
	minirt->cam.is_init = true;
	return (0);
}
