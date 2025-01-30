/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arithmetic_vector_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acancel <acancel@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 16:14:10 by anfichet          #+#    #+#             */
/*   Updated: 2025/01/29 13:28:33 by acancel          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "vector_bonus.h"

t_vec3	add_vec3(t_vec3 a, t_vec3 b)
{
	return ((t_vec3){a.x + b.x, a.y + b.y, a.z + b.z});
}

t_vec3	sub_vec3(t_vec3 a, t_vec3 b)
{
	return ((t_vec3){a.x - b.x, a.y - b.y, a.z - b.z});
}

double	distance_vec3(t_vec3 a, t_vec3 b)
{
	double	dx;
	double	dy;
	double	dz;
	double	res;

	dx = b.x - a.x;
	dy = b.y - a.y;
	dz = b.z - a.z;
	res = dx * dx + dy * dy + dz * dz;
	return (res);
}
