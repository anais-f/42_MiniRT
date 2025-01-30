/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_mlx.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acancel <acancel@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 16:35:58 by acancel           #+#    #+#             */
/*   Updated: 2024/12/12 16:35:59 by acancel          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "display_mlx.h"
#include <stdlib.h>

void	mlx_destroy_all(t_img *img)
{
	if (img->img)
		mlx_destroy_image(img->mlx_ptr, img->img);
	if (img->win_ptr)
		mlx_destroy_window(img->mlx_ptr, img->win_ptr);
	if (img->mlx_ptr)
	{
		mlx_destroy_display(img->mlx_ptr);
		free(img->mlx_ptr);
	}
	return ;
}
