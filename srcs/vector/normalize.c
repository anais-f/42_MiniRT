/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normalize.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anfichet <anfichet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 16:14:29 by anfichet          #+#    #+#             */
/*   Updated: 2024/12/12 16:14:30 by anfichet         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"
#include <math.h>

double	norm_vec3(t_vec3 a)
{
	double	length;

	length = sqrtf(a.x * a.x + a.y * a.y + a.z * a.z);
	return (length);
}

double	norm_vec2(t_vec2 a)
{
	double	length;

	length = sqrtf(a.x * a.x + a.y * a.y);
	return (length);
}

t_vec3	normalize_vec3(t_vec3 a)
{
	double	length;

	length = norm_vec3(a);
	a.x = (a.x / length);
	a.y = (a.y / length);
	a.z = (a.z / length);
	return (a);
}

t_vec2	normalize_vec2(t_vec2 a)
{
	double	length;

	length = norm_vec2(a);
	a.x = (a.x / length);
	a.y = (a.y / length);
	return (a);
}

/* to compare 2 vectors' norms without sqrt -> more efficience */
int	compare_norm_vec3(t_vec3 a, t_vec3 b)
{
	double	length_a;
	double	length_b;

	length_a = a.x * a.x + a.y * a.y + a.z * a.z;
	length_b = b.x * b.x + b.y * b.y + b.z * b.z;
	if (length_a > length_b)
		return (1);
	else if (length_a < length_b)
		return (2);
	else if (length_a == length_b)
		return (3);
	return (0);
}
