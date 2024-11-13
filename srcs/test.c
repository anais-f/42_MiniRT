#include "miniRT.h"
#include "libft.h"
#include "mlx_int.h"

typedef struct s_data
{
	void			*img;
	void			*mlx;
	void			*win;
	char			*addr;
	int				bits_per_pixel;
	int				line_length;
	int				endian;
	double			win_size_max;
	double			win_size_min;
	double			offset_x;
	double			offset_y;
}				t_data;

typedef struct s_coord
{
	float	x;
	float	y;
	float	z;
}				t_coord;

typedef struct s_factor
{
	float	a;
	float	b;
	float	c;
}				t_factor;



double	scaling_x(t_data *data, double coordinate, double osw_max)
{
	double	new_coordinate;

	(void) osw_max;
	new_coordinate = coordinate - data->win_size_max / 2;
	return (new_coordinate);
}

double	scaling_y(t_data *data, double coordinate, double osw_max)
{
	double	new_coordinate;

	(void) osw_max;
	new_coordinate = coordinate - data->win_size_max / 2;
	return (new_coordinate);
}

int	kb_event(int keycode, t_data *data)
{
	if (keycode == ESC_KB)
		mlx_loop_end(data->mlx);
	return (0);
}

void	mlx_destroy_all(t_data *data)
{
		mlx_destroy_image(data->mlx, data->img);
	if (data->win)
		mlx_destroy_window(data->mlx, data->win);
	if (data->mlx)
	{
		mlx_destroy_display(data->mlx);
		free(data->mlx);
	}
	return ;
}

int	mlx_init_protected(t_data *data)
{
	(void)data;
	data->mlx = mlx_init();
	if (!data->mlx)
		return (-1);
	data->win = mlx_new_window(data->mlx, SIZE_W, SIZE_H, "miniRT");
	data->img = mlx_new_image(data->mlx, SIZE_W, SIZE_H);
	if (!data->win || !data->img)
	{
		mlx_destroy_all(data);
		return (-1);
	}
	data->addr = mlx_get_data_addr(data->img, &data->bits_per_pixel,
			&data->line_length, &data->endian);
	return (0);
}

long ft_pow(int num)
{
	return (num * num);
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;
	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

int mouse_click(int button, int x, int y, t_data *data) 
{
	int	nx;
	int ny;

	if (button == 1)
	{
		printf("Mouse Clicked at: X: %d, Y: %d\n", x, y);
		nx = x - (data->win_size_max / 2);
		ny = y - (data->win_size_max / 2);
		printf("Mouse Clicked at: Nx: %d, Ny: %d\n", nx, ny);
	}
	return 0;
}

int create_rgb(int r, int g, int b) {
	return ((r << 16) | (g << 8) | b);
}

int test(void)
{
	t_data	data;
	// t_coord pixel; /*Where x = red, y = green & z = blue*/
	// t_coord point;

	t_coord camera_center;
	int	x;
	int	y;

	/*Camera*/
	double	focal_length = 1.0;
	double	viewport_height = 2.0;
	double	viewport_width = viewport_height * ((double)(SIZE_W) / SIZE_H);
	camera_center = (t_coord){0, 0, 0};



	x = 0;
	y = 0;
	data.win_size_max = SIZE_W;
	if (mlx_init_protected(&data) != 0)
		return (-1);
	printf("Hello Nana_ïs\n");
	while (y <= SIZE_H)
	{
		x = 0;
		printf("\rScanlines remaining %d ", (SIZE_H - y));
		fflush(stdout);
		usleep(500);
		while (x <= SIZE_W)
		{
			// nx = (double)x;
			// ny = (double)y;
			// r = nx / (SIZE_W);
			// g = ny / (SIZE_H);
			// b = 0.0;
			double	ir = (1.0 - (0.5 * x + 1.0)* 1 + (0.5 * x + 1.0)* 0.5);
			double	ig = (1.0 - (0.5 * x + 1.0)* 1 + (0.5 * x + 1.0)* 0.7);
			double	ib = (1.0 - (0.5 * x + 1.0)* 1 + (0.5 * x + 1.0)* 1);
			int color = create_rgb((255.999 * (double)x / SIZE_W), (255.999 * (double)y / SIZE_H), 0);
			// int	color = create_rgb(ir , ig, ib);
			my_mlx_pixel_put(&data, x, y, color);
			
			ir = 0.0;
			ig = ir;
			ib = ir;
			x++;
		}
		y++;
	}
	printf("\nDone				\n");
	mlx_put_image_to_window(data.mlx, data.win, data.img, 0, 0);
	mlx_mouse_hook(data.win, mouse_click, &data);
	mlx_hook(data.win, 2, 1L << 0, kb_event, &data);
	mlx_hook(data.win, 17, 0L, mlx_loop_end, data.mlx);
	mlx_loop(data.mlx);
	mlx_destroy_all(&data);
	return (0);
}
	// int cx = 100; // Centre en x (coordonnée centrale)
	// int cy = 100; // Centre en y (coordonnée centrale)
	// int r = 100;  // Rayon du cercle
	// int lx = 440; // Position x de la lumière
	// int ly = 440; // Position y de la lumière

	// y = cy - r;
	// while (y <= cy + r)
	// {
	// 	x = cx - r;
	// 	while (x <= cx + r)
	// 	{
	// 		// Calculer si le point est à l'intérieur du cercle (surface de la sphère)
	// 		int dx = x - cx; // = (x - decalage)
	// 		int dy = y - cy; // = (y - decalage)
	// 		if (dx * dx + dy * dy <= r * r) // equation cercle 
	// 		{
	// 			// Calculer la normale au point (x, y)
	// 			float nx = dx / (float)r;
	// 			float ny = dy / (float)r;

	// 			// Calculer la direction de la lumière
	// 			float lx_norm = (lx - x) / (float)r;
	// 			float ly_norm = (ly - y) / (float)r;

	// 			// Calculer l'intensité de la lumière en fonction de la normale
	// 			float dot_product = (nx * lx_norm + ny * ly_norm);
	// 			float intensity = fmax(0, dot_product); // L'intensité est comprise entre 0 et 1

	// 			// Couleur avec dégradé (0xFFFFFF est blanc pur, multiplié par l'intensité)
	// 			int color = (int)(intensity * 255) << 16 | (int)(intensity * 255) << 8 | (int)(intensity * 255);

	// 			// Dessiner le pixel avec la couleur calculée
	// 			my_mlx_pixel_put(&data, x, y, color); //color
	// 		}
	// 		x++;
	// 	}
	// 	y++;
	// }









	// y = 0;
	// while (y <= cy + r)
	// {
	// 	x = 0;
	// 	while (x <= cx + r)
	// 	{
	// 		// Vérifier si le point (x, y) est dans le cercle
	// 		// if ((x - cx) * (x - cx) + (y - cy) * (y - cy) <= r * r)
	// 		if ((x - 540) * (x - 540) + (y - 540) * (y - 540) <= r * r)
	// 		{
	// 			my_mlx_pixel_put(&data, x, y, 0x00FF0000); // Dessiner le pixel rouge si dans le cercle
	// 		}
	// 		x++;
	// 	}
	// 	y++;
	// }

	// while (y <= ymax)
	// {
	// 	while (x <= xmax)
	// 	{
	// 		my_mlx_pixel_put(&data, x, y, 0x00FF0000);
	// 		x++;
	// 	}
	// 	y++;
	// 	x = 440;
 	// }
