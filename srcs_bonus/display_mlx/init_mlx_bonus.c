/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acancel <acancel@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 16:36:10 by acancel           #+#    #+#             */
/*   Updated: 2025/01/29 13:27:00 by acancel          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "display_mlx_bonus.h"

int	mlx_init_protected(t_img *img)
{
	img->mlx_ptr = mlx_init();
	if (!img->mlx_ptr)
		return (-1);
	img->win_ptr = mlx_new_window(img->mlx_ptr, WIDTH_WIN, HEIGHT_WIN, \
									"miniRT");
	img->img = mlx_new_image(img->mlx_ptr, WIDTH_WIN, HEIGHT_WIN);
	if (!img->win_ptr || !img->img)
	{
		mlx_destroy_all(img);
		return (-1);
	}
	img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel,
			&img->line_length, &img->endian);
	return (0);
}
