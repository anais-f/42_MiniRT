/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_cam.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anfichet <anfichet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 15:20:36 by acancel           #+#    #+#             */
/*   Updated: 2024/12/12 15:01:23 by anfichet         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	parse_camera(char **line_parsed, t_minirt *minirt)
{
	if (minirt->cam.is_init)
	{
		printf("Error :\nCamera already set\n");
		return (1);
	}
	if (arr_len(line_parsed) != 4)
	{
		printf("Error :\nCamera must have only three parameters\n");
		return (2);
	}
	if (parse_coordinates(line_parsed[1], &minirt->cam.position) || \
			parse_coordinates(line_parsed[2], &minirt->cam.direction) \
			|| errno == ERANGE)
	{
		printf("Error :\nParsing camera coordinates\n");
		return (3);
	}
	minirt->cam.fov = ft_atof(line_parsed[3]);
	if (check_range_items(minirt, CAMERA))
	{
		printf("Error :\nCamera parameters out of range\n");
		return (4);
	}
	minirt->cam.is_init = true;
	return (0);
}
