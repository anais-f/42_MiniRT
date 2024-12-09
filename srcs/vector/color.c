/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anfichet <anfichet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 17:56:48 by anfichet          #+#    #+#             */
/*   Updated: 2024/12/09 17:56:49 by anfichet         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_vec3	color_to_vec3(t_color color)
{
	t_vec3	vec;

	vec.x = (double)color.r / 255.0f;
	vec.y = (double)color.g / 255.0f;
	vec.z = (double)color.b / 255.0f;
	return (vec);
}

t_color	vec3_to_color(t_vec3 vec)
{
	t_color	color;

	color = (t_color){0xFFFFFFFF};
	if (vec.x <= 1)
		color.r = vec.x * 255.f;
	if (vec.y <= 1)
		color.g = vec.y * 255.f;
	if (vec.z <= 1)
		color.b = vec.z * 255.f;
	return (color);
}

t_vec3	add_color_vec3(t_vec3 a, t_vec3 b)
{
	t_vec3	result;

	result.x = a.x + b.x;
	result.y = a.y + b.y;
	result.z = a.z + b.z;
	if (result.x > 1)
		result.x = 1;
	if (result.y > 1)
		result.y = 1;
	if (result.z > 1)
		result.z = 1;
	return (result);
}
