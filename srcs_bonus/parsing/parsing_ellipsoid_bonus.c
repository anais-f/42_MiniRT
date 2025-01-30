/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_ellipsoid_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acancel <acancel@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 16:37:40 by acancel           #+#    #+#             */
/*   Updated: 2025/01/30 17:24:52 by acancel          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT_bonus.h"

int	parse_ellipsoid(char **line_parsed, t_minirt *minirt)
{
	t_object	object;

	if (arr_len(line_parsed) != 6)
	{
		printf("Error :\nEllipsoid must have only five parameters\n");
		return (1);
	}
	if (parse_coordinates(line_parsed[1], &object.position) \
		|| parse_color(line_parsed[5], &object.color) \
		|| !is_valid_float(line_parsed[2]) || !is_valid_float(line_parsed[3]) \
		|| !is_valid_float(line_parsed[4]))
		return (2);
	object.type = ELLIPSOID;
	object.spec.el.radius.x = (double)ft_atof(line_parsed[2]) / 2.f;
	object.spec.el.radius.y = (double)ft_atof(line_parsed[3]) / 2.f;
	object.spec.el.radius.z = (double)ft_atof(line_parsed[4]) / 2.f;
	if (object.spec.el.radius.x <= 0 || object.spec.el.radius.y <= 0 \
		|| object.spec.el.radius.z <= 0)
	{
		printf("Error :\nEllipsoid radius must be positive\n");
		return (3);
	}
	if (add_object(object, &minirt->objects))
		return (4);
	return (0);
}
