#include "miniRT.h"

int	check_argv(int argc, char *str)
{
	const char	str_check[] = ".rt";
	size_t		i;
	size_t		len_str;

	if (argc != 2)
	{
		printf("Invalid number of arguments\n");
		return (1);
	}
	i = 0;
	len_str = ft_strlen(str);
	if (len_str < 4)
	{
		printf("Invalid parameter\n");
		return (1);
	}
	if (ft_strncmp(str_check, &str[len_str - 3], 4) != 0)
	{
		printf("Invalid file\n");
		return (1);
	}
	return (0);
}

int main(int argc, char **argv)
{

	t_minirt	minirt;

	//check l'input check argv
	if (check_argv(argc, argv[1]) == 1)
		return (1);

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

	//MLX
	// init mlx
	// laucnh event
	// launch loop
	// destroy mlx



	return (0);
}


