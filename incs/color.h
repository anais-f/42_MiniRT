/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anfichet <anfichet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 16:11:51 by anfichet          #+#    #+#             */
/*   Updated: 2024/12/12 16:11:52 by anfichet         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLOR_H
# define COLOR_H

# include <stdint.h>
# include <vector.h>

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