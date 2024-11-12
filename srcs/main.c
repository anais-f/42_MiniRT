#include "miniRT.h"

int main(int argc, char **argv)
{
	t_minirt	minirt;
	(void)argc;
	(void)argv;

	//check l'input check argv
	// if (check_argv(argc, argv[1]) == 1)
	// 	return (1);

	// ouvrir le fichier
	// parser le fichier


	if (mlx_init_protected(&minirt.img) != 0)
	{
		// free les trucs de la scene ?
		return (-1);
	}


	/************************* */
	test(&minirt.img);










	/**************************** */
	mlx_put_image_to_window(minirt.img.mlx_ptr, minirt.img.win_ptr, minirt.img.img, 0, 0); //  a supprimer apres car compris dans loop
	mlx_launch_event_and_loop(&minirt.img); // ici le put image  	
	mlx_destroy_all(&minirt.img);

	return (0);
}

	//MLX
	// init mlx
	// laucnh event
	// launch loop
	// destroy mlx

