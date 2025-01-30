/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anfichet <anfichet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 17:55:39 by anfichet          #+#    #+#             */
/*   Updated: 2024/12/09 17:55:40 by anfichet         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef CAMERA_H
# define CAMERA_H

# include "vector.h"
# include <stdbool.h>

typedef struct s_minirt	t_minirt;

typedef struct s_camera
{
	t_vec3	position;
	t_vec3	direction;
	t_vec3	world_dir;
	float	fov;
	float	fov_scale;
	float	aspect_ratio;
	bool	is_init;
	t_mat	rot_mat;
	float	theta;
	t_vec3	normal_rot;
}	t_camera;

void	move_camera(t_minirt *mini, t_vec3 direction, float distance);
t_mat	rodrigues_rot(t_minirt *mini, t_vec3 axis, float theta);
float	theta_calc(t_vec3 u, t_vec3 v);

#endif