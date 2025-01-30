/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   divide.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anfichet <anfichet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 17:56:54 by anfichet          #+#    #+#             */
/*   Updated: 2024/12/09 17:56:55 by anfichet         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

t_vec3	div_vec3(t_vec3 a, t_vec3 b)
{
	return ((t_vec3){a.x / b.x, a.y / b.y, a.z / b.z});
}

t_vec3	div_denom_vec3(t_vec3 a, double nb)
{
	return ((t_vec3){a.x / nb, a.y / nb, a.z / nb});
}

t_vec3	div_num_vec3(t_vec3 a, double nb)
{
	return ((t_vec3){nb / a.x, nb / a.y, nb / a.z});
}
