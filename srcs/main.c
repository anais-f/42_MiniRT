/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anfichet <anfichet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 16:35:54 by acancel           #+#    #+#             */
/*   Updated: 2025/02/05 15:09:00 by anfichet         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	main(int argc, char **argv)
{
	t_minirt	rt;

	ft_bzero(&rt, sizeof(t_minirt));
	if (check_argv(argc, argv[1]) == 1 || parsing_map(&rt, argv[1]))
	{
		array_free(&rt.objects);
		array_free(&rt.lights);
		return (1);
	}
	init_minirt(&rt);
	if (mlx_init_protected(&rt.img) != 0)
	{
		mlx_destroy_all(&rt.img);
		array_free(&rt.objects);
		array_free(&rt.lights);
		return (-1);
	}
	rt.cam.rot_mat = rodrigues_rot(&rt, rt.cam.normal_rot, rt.cam.theta);
	draw_image(&rt);
	mlx_launch_event_and_loop(&rt.img, &rt);
	mlx_destroy_all(&rt.img);
	array_free(&rt.objects);
	array_free(&rt.lights);
	return (0);
}
