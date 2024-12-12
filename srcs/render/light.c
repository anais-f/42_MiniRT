/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anfichet <anfichet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 16:13:36 by anfichet          #+#    #+#             */
/*   Updated: 2024/12/12 16:13:49 by anfichet         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static t_vec3	get_ambient_light(t_minirt *minirt)
{
	t_vec3	ambient_light;

	ambient_light = color_to_vec3(minirt->ambient_light.color);
	ambient_light = mult_nb_vec3(ambient_light, \
						minirt->ambient_light.brightness);
	return (ambient_light);
}

/* Inversion of substract to have the ray from object to light */
static t_vec3	get_light_dir(t_object light, t_hit hit)
{
	t_vec3	light_dir;

	light_dir = sub_vec3(light.position, hit.position);
	light_dir = normalize_vec3(light_dir);
	return (light_dir);
}

static double	get_specular_reflection(t_object light, t_hit hit)
{
	t_vec3	light_dir;
	t_vec3	reflection_dir;
	double	specular_intensity;
	double	specular_coef;

	light_dir = mult_nb_vec3(get_light_dir(light, hit), -1);
	reflection_dir = sub_vec3(light_dir, mult_nb_vec3(hit.normal, \
						2.0f * dot_vec3(hit.normal, light_dir)));
	specular_coef = dot_vec3(reflection_dir, \
						mult_nb_vec3(hit.ray.direction, -1));
	if (specular_coef < 0.0f)
	{
		specular_coef = 0.0f;
		return (specular_coef);
	}
	specular_intensity = pow(specular_coef, SPECULAR);
	return (specular_intensity);
}

static double	get_light_bright(t_minirt *minirt, t_object light, t_hit hit)
{
	t_vec3	light_dir;
	double	light_intensity;

	light_dir = get_light_dir(light, hit);
	light_intensity = dot_vec3(hit.normal, light_dir) + \
						get_specular_reflection(light, hit);
	if (light_intensity < 0.0f)
	{
		light_intensity = 0.0f;
		return (light_intensity);
	}
	if (check_ray_to_light(minirt, hit, light, light_dir) == false)
	{
		light_intensity = 0.0f;
		return (light_intensity);
	}
	light_intensity = light_intensity * light.spec.light.brightness;
	return (light_intensity);
}

t_vec3	get_scene_light(t_minirt *minirt, t_hit hit)
{
	t_vec3		light_color;
	double		light_bright;
	size_t		i;
	t_object	light;
	t_vec3		final_color;

	final_color = (t_vec3){0, 0, 0};
	i = 0;
	while (i < minirt->lights.size)
	{
		light = *minirt->lights.array[i];
		light_bright = get_light_bright(minirt, light, hit);
		light_color = color_to_vec3(light.color);
		light_color = mult_nb_vec3(light_color, light_bright);
		i++;
		final_color = add_color_vec3(light_color, final_color);
	}
	final_color = add_color_vec3(final_color, get_ambient_light(minirt));
	return (final_color);
}
