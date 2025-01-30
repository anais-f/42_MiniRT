/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cam_move.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anfichet <anfichet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 17:56:05 by anfichet          #+#    #+#             */
/*   Updated: 2024/12/09 17:56:06 by anfichet         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	move_camera(t_minirt *mini, t_vec3 direction, float distance)
{
	t_vec3	delta;

	delta = mult_nb_vec3(direction, distance);
	mini->cam.position = add_vec3(mini->cam.position, delta);
}
