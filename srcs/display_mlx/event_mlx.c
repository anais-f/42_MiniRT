#include "miniRT.h"
# include <stdio.h>

static void move_camera(t_minirt *mini, t_vec3 direction, float distance)
{
    t_vec3 delta;

    delta = mult_nb_vec3(direction, distance);
    mini->cam.position = add_vec3(mini->cam.position, delta);
}

t_vec3 rotate_vec3(t_vec3 v, t_vec3 axis, float angle)
{
    t_vec3 rotated_v;
    float cos_angle = cos(angle);
    float sin_angle = sin(angle);
    
    // Calcul de la rotation de Rodrigues
    rotated_v.x = v.x * cos_angle + cross_vec3(axis, v).x * sin_angle + axis.x * dot_vec3(axis, v) * (1 - cos_angle);
    rotated_v.y = v.y * cos_angle + cross_vec3(axis, v).y * sin_angle + axis.y * dot_vec3(axis, v) * (1 - cos_angle);
    rotated_v.z = v.z * cos_angle + cross_vec3(axis, v).z * sin_angle + axis.z * dot_vec3(axis, v) * (1 - cos_angle);

    return rotated_v;
}

void	rotate_camera(t_minirt *mini, t_vec3 axis, float angle)
{
	float	theta;

	mini->cam.direction = normalize_vec3(rotate_vec3(mini->cam.direction, axis, angle));
	theta = theta_calc(mini->cam.world_dir, mini->cam.direction);
	mini->cam.rot_mat = rodrigues_rot(mini, axis, angle);
//	return (mini->cam.direction);
}



int	kb_event(int key, t_minirt *mini)
{
	float move_speed = 0.3;
    t_vec3 up = {0, 1, 0};
	float angle = 90 * mini->to_radian;

	if (key == ESC_KB)
		mlx_loop_end(mini->img.mlx_ptr);
	if (key == W_KB)
		move_camera(mini, mini->cam.direction, move_speed);
    else if (key == S_KB) // on se deplace sur l'axe z
		move_camera(mini, mini->cam.direction, -move_speed);
    else if (key == A_KB)
		move_camera(mini, cross_vec3(up, mini->cam.direction), -move_speed);
    else if (key == D_KB) // on se deplace sur l'axe x
		move_camera(mini, cross_vec3(up, mini->cam.direction), move_speed);
	else if (key == R_KB) // on se deplace sur l'axe y
		move_camera(mini, up, move_speed);
    else if (key == F_KB)
		move_camera(mini, up, -move_speed);
	else if (key == Q_KB)
		rotate_camera(mini, up, angle);
	else if (key == E_KB)
		rotate_camera(mini, up, -angle);





	render_scene(mini, &mini->img);
    mlx_put_image_to_window(mini->img.mlx_ptr, mini->img.win_ptr, mini->img.img, 0, 0);
	return (0);
}

int	ft_mouse_event(int button, int x, int y, t_img *img)
{
	(void) x;
	(void) y;
	(void)button;
	(void)img;
	return (0);
}

void	mlx_launch_event_and_loop(t_img *img)
{
	mlx_mouse_hook(img->win_ptr, ft_mouse_event, img);
	mlx_hook(img->win_ptr, 02, 1L << 0, kb_event, img);
	mlx_hook(img->win_ptr, 17, 0L, mlx_loop_end, img->mlx_ptr);
	mlx_loop(img->mlx_ptr);
}
