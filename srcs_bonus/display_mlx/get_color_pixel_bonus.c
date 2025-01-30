/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_color_pixel_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acancel <acancel@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 16:13:04 by anfichet          #+#    #+#             */
/*   Updated: 2025/01/29 13:26:57 by acancel          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT_bonus.h"

t_color	get_color_pixel(t_minirt *minirt, t_hit hit)
{
	t_vec3	light_color;
	t_color	final_color;

	if (hit.dst == -1)
		return ((t_color){0xFF000000});
	light_color = get_scene_light(minirt, hit);
	light_color.x *= (color_to_vec3(hit.object.color)).x;
	light_color.y *= (color_to_vec3(hit.object.color)).y;
	light_color.z *= (color_to_vec3(hit.object.color)).z;
	final_color = vec3_to_color(light_color);
	return (final_color);
}
