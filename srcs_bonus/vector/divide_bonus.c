/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   divide_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acancel <acancel@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 16:14:16 by anfichet          #+#    #+#             */
/*   Updated: 2025/01/29 13:28:44 by acancel          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "vector_bonus.h"

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
