#include "miniRT.h"


// int	main()
// {
// 	t_mat a;
// 	t_vec3 vec;
// 	t_vec3 c;

// 	vec.x = 1;
// 	vec.y = 2;
// 	vec.z = 3;
// 	c.x = 0;
// 	c.y = 0;
// 	c.z = 0;

// 	a = matrix_identity();

// 	a.mat[0][0] = 2;
// 	a.mat[0][1] = 3;
// 	a.mat[0][2] = 4;
// 	a.mat[1][0] = 5;
// 	a.mat[1][1] = 6;
// 	a.mat[1][2] = 7;
// 	a.mat[2][0] = 8;
// 	a.mat[2][1] = 9;
// 	a.mat[2][2] = 1;


// 	printf("Matrix A\n");
// 	print_matrix(a);


// 	c = mult_vec3_matrix(vec, a);

// 	printf("vec = %f %f %f\n", c.x, c.y, c.z);

// }



int main(int argc, char **argv)
{
	t_minirt	minirt;

	minirt = (t_minirt){0}; // bzero ? 
	if (check_argv(argc, argv[1]) == 1)
		return (1);

	array_init(&minirt.objects);

	prasing_map(&minirt, argv[1]);
	//print_parsing(&minirt);
	init_minirt(&minirt);
	

	if (mlx_init_protected(&minirt.img) != 0)
	{
		// free les trucs de la scene ?
		return (-1);
	}

	/************************* */
	camera(&minirt);	

	render_scene(&minirt, &minirt.img);

	/**************************** */
	mlx_put_image_to_window(minirt.img.mlx_ptr, minirt.img.win_ptr, minirt.img.img, 0, 0); //  a supprimer apres car compris dans loop
	mlx_launch_event_and_loop(&minirt.img); // ici le put image  	
	mlx_destroy_all(&minirt.img);
	array_free(&minirt.objects);
	return (0);
}

	//MLX
	// init mlx
	// laucnh event
	// launch loop
	// destroy mlx

