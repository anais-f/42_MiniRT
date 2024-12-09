/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arithmetic_vector.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anfichet <anfichet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 17:56:46 by anfichet          #+#    #+#             */
/*   Updated: 2024/12/09 17:56:47 by anfichet         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

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
