/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anfichet <anfichet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 17:56:38 by anfichet          #+#    #+#             */
/*   Updated: 2024/12/11 10:23:27 by anfichet         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static void	calc_pixel_and_check_obj(t_minirt *minirt, t_hit *hit, int x, int y)
{
	size_t	i;
	t_hit	tp_hit;
	double	dst;

	ft_memset(hit, 0, sizeof(t_hit));
	hit->dst = -1;
	hit->ray = create_ray_from_cam(minirt, x, y);
	hit->ray.direction = normalize_vec3(\
			mult_vec3_matrix(hit->ray.direction, minirt->cam.rot_mat));
	i = 0;
	while (i < minirt->objects.size)
	{
		tp_hit = *hit;
		dst = object_intersection(hit->ray, *minirt->objects.array[i], &tp_hit);
		if (dst != -1 && (dst < hit->dst || hit->dst == -1))
		{
			*hit = tp_hit;
			hit->dst = dst;
			hit->object = *minirt->objects.array[i];
		}
		i++;
	}
}

void	render_scene(t_minirt *minirt, t_img *img)
{
	int		x;
	int		y;
	t_hit	hit;

	y = 0;
	while (y <= HEIGHT_WIN)
	{
		x = 0;
		while (x <= WIDTH_WIN)
		{
			calc_pixel_and_check_obj(minirt, &hit, x, y);
			hit_point(minirt, hit.ray, &hit);
			minirt->color = get_color_pixel(minirt, hit);
			my_mlx_pixel_put(img, x, y, minirt->color.color);
			x++;
		}
		y++;
	}
}
