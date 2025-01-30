/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multiply_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acancel <acancel@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 16:14:26 by anfichet          #+#    #+#             */
/*   Updated: 2025/01/29 13:28:53 by acancel          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "vector_bonus.h"
#include "camera_bonus.h"

t_vec3	mult_vec3(t_vec3 a, t_vec3 b)
{
	return ((t_vec3){a.x * b.x, a.y * b.y, a.z * b.z});
}

t_vec3	mult_nb_vec3(t_vec3 a, double nb)
{
	return ((t_vec3){a.x * nb, a.y * nb, a.z * nb});
}

t_vec3	mult_vec3_matrix(t_vec3 a, t_mat b)
{
	t_vec3	vec;

	vec.x = a.x * b.mat[0][0] + a.y * b.mat[0][1] + a.z * b.mat[0][2];
	vec.y = a.x * b.mat[1][0] + a.y * b.mat[1][1] + a.z * b.mat[1][2];
	vec.z = a.x * b.mat[2][0] + a.y * b.mat[2][1] + a.z * b.mat[2][2];
	return (vec);
}
