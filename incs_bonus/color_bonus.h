/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acancel <acancel@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 16:11:51 by anfichet          #+#    #+#             */
/*   Updated: 2025/01/30 17:13:06 by acancel          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLOR_BONUS_H
# define COLOR_BONUS_H

# include <stdint.h>
# include "vector_bonus.h"

typedef struct s_minirt	t_minirt;
typedef struct s_hit	t_hit;

typedef union u_color
{
	__uint32_t	color;
	struct
	{
		__uint8_t	b;
		__uint8_t	g;
		__uint8_t	r;
		__uint8_t	a;
	};
}	t_color;

t_vec3	color_to_vec3(t_color color);
t_color	vec3_to_color(t_vec3 vec);
t_vec3	add_color_vec3(t_vec3 a, t_vec3 b);
t_color	get_color_pixel(t_minirt *minirt, t_hit hit);

#endif