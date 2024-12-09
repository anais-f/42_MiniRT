#include "miniRT.h"

int	kb_event(int key, t_minirt *mini)
{
	float	move_speed;
	t_vec3	up ;

	up = (t_vec3){0, 1, 0};
	move_speed = 0.5;
	if (key == ESC_KB)
		mlx_loop_end(mini->img.mlx_ptr);
	if (key == W_KB)
		move_camera(mini, mini->cam.direction, move_speed);
	else if (key == S_KB)
		move_camera(mini, mini->cam.direction, -move_speed);
	else if (key == A_KB)
		move_camera(mini, cross_vec3(up, mini->cam.direction), -move_speed);
	else if (key == D_KB)
		move_camera(mini, cross_vec3(up, mini->cam.direction), move_speed);
	else if (key == R_KB)
		move_camera(mini, up, move_speed);
	else if (key == F_KB)
		move_camera(mini, up, -move_speed);
	render_scene(mini, &mini->img);
	mlx_put_image_to_window(mini->img.mlx_ptr, mini->img.win_ptr, \
							mini->img.img, 0, 0);
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
