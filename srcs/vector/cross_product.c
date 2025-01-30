/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cross_product.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anfichet <anfichet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 17:56:50 by anfichet          #+#    #+#             */
/*   Updated: 2024/12/09 17:56:51 by anfichet         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

/* The cross product gives a new vector -> a * b = c.
Several applications : 
- compute the normal vectors of surfaces, for lighting calculations
	(to determine how light interacts with surfaces).
- calculate how much light is reflected or absorbed, which is essential 
	for shading
- reflections and refractions : help to determine the angle for light 
	reflect in reflection, or used
to apply Snell's law for refraction
- calculate orthogonal vectors, used to define camera axes
- calculating area of parallelgoram formed by 2 vectors.
If cross product = 0 -> both vectors are parallel
*/

t_vec3	cross_vec3(t_vec3 a, t_vec3 b)
{
	t_vec3	result;

	result.x = a.y * b.z - a.z * b.y;
	result.y = a.z * b.x - a.x * b.z;
	result.z = a.x * b.y - a.y * b.x;
	return (result);
}
