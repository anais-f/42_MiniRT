/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   caps.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acancel <acancel@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 16:36:30 by acancel           #+#    #+#             */
/*   Updated: 2024/12/12 16:36:31 by acancel          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	calculate_cap_positions(t_object *cy)
{
	double	height;

	height = cy->spec.cy.height;
	cy->spec.cy.cap_pos[0] = cy->position;
	cy->spec.cy.cap_pos[1] = add_vec3(cy->position, \
		mult_nb_vec3(cy->direction, height));
	return ;
}

void	calculate_cap_intersections(t_ray ray, t_object *cy, double radius)
{
	int		i;
	double	denom;
	double	t;
	t_vec3	cap_point;

	i = 0;
	while (i < 2)
	{
		denom = dot_vec3(ray.direction, cy->direction);
		cy->spec.cy.t_cap[i] = -1;
		if (fabs(denom) > 1e-6)
		{
			t = dot_vec3(sub_vec3(cy->spec.cy.cap_pos[i], ray.origin), \
				cy->direction) / denom;
			if (t > 0)
			{
				cap_point = add_vec3(ray.origin, \
					mult_nb_vec3(ray.direction, t));
				if (distance_vec3(cap_point, cy->spec.cy.cap_pos[i]) \
						<= radius * radius)
					cy->spec.cy.t_cap[i] = t;
			}
		}
		i++;
	}
}
/*Above, the variable denom and the conditions to be checked around it
are used to avoid divisions by 0 with an accuracy of
10e^-6
*/