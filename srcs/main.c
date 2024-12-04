#include "miniRT.h"

int	main(int argc, char **argv)
{
	t_minirt	minirt;

	ft_bzero(&minirt, sizeof(t_minirt));
	array_init(&minirt.objects);
	if (check_argv(argc, argv[1]) == 1 || parsing_map(&minirt, argv[1]))
	{
		array_free(&minirt.objects);
		return (1);
	}
	init_minirt(&minirt);
	if (mlx_init_protected(&minirt.img) != 0)
	{
		mlx_destroy_all(&minirt.img);
		array_free(&minirt.objects);
		return (-1);
	}
	camera(&minirt, minirt.cam.direction, minirt.cam.world_dir);
	render_scene(&minirt, &minirt.img);
	mlx_put_image_to_window(minirt.img.mlx_ptr, \
		minirt.img.win_ptr, minirt.img.img, 0, 0);
	mlx_launch_event_and_loop(&minirt.img);
	mlx_destroy_all(&minirt.img);
	array_free(&minirt.objects);
	return (0);
}
