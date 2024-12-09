#include "miniRT.h"

int	main(int argc, char **argv)
{
	t_minirt	rt;

	ft_bzero(&rt, sizeof(t_minirt));
	array_init(&rt.objects);
	if (check_argv(argc, argv[1]) == 1 || parsing_map(&rt, argv[1]))
	{
		array_free(&rt.objects);
		return (1);
	}
	init_rt(&rt);
	if (mlx_init_protected(&rt.img) != 0)
	{
		mlx_destroy_all(&rt.img);
		array_free(&rt.objects);
		return (-1);
	}
	rt.cam.rot_mat = rodrigues_rot(&rt, rt.cam.normal_rot, rt.cam.theta);
	render_scene(&rt, &rt.img);
	mlx_put_image_to_window(rt.img.mlx_ptr, rt.img.win_ptr, rt.img.img, 0, 0);
	mlx_launch_event_and_loop(&rt.img);
	mlx_destroy_all(&rt.img);
	array_free(&rt.objects);
	return (0);
}
