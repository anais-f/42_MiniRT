#include "display_mlx.h"

int	kb_event(int keycode, t_img *img)
{
	if (keycode == ESC_KB)
		mlx_loop_end(img->mlx_ptr);
	return (0);
}

int	ft_mouse_event(int button, int x, int y, t_img *img)
{
	(void) x;
	(void) y;
	(void)button;
	(void)img;
	// if (button == 4)
	// 	img->zoom *= 1.1;
	// if (button == 5)
	// 	img->zoom *= 0.9;
	return (0);
}

void	mlx_launch_event_and_loop(t_img *img)
{
	mlx_mouse_hook(img->win_ptr, ft_mouse_event, img);
	mlx_hook(img->win_ptr, 02, 1L << 0, kb_event, img);
	mlx_hook(img->win_ptr, 17, 0L, mlx_loop_end, img->mlx_ptr);
	mlx_loop(img->mlx_ptr);
}
