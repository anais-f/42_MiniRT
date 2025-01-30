/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cam_move_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acancel <acancel@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 16:12:41 by anfichet          #+#    #+#             */
/*   Updated: 2025/01/29 13:26:42 by acancel          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT_bonus.h"

void	move_camera(t_minirt *mini, t_vec3 direction, float distance)
{
	t_vec3	delta;

	delta = mult_nb_vec3(direction, distance);
	mini->cam.position = add_vec3(mini->cam.position, delta);
}
