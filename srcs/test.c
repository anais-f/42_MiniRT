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


double	scaling_x(t_data *data, double coordinate, double osw_max)
{
	double	new_coordinate;
	
	new_coordinate = (1. - 0.) * coordinate / \
			osw_max + (data->win_size_min + data->offset_x);
	return (new_coordinate);
}

double	scaling_y(t_data *data, double coordinate, double osw_max)
{
	double	new_coordinate;

	new_coordinate = (1.0 - 0.) * coordinate / \
			osw_max + (data->win_size_min + data->offset_y);
	return (-new_coordinate + 1);
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

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;
	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

int mouse_click(int button, int x, int y, t_data *data) {
	(void)data;
    if (button == 1) { // Vérifie si c'est un clic gauche
        printf("Mouse Clicked at: X: %d, Y: %d\n", x, y);
    }
    return 0;
}

int test(void)
{
	t_data	data;
	double new_y;
	double new_x = 0;
	int	x;
	int	y;
	int	xmax;
	int	ymax;

	x = 0;
	y = 0;
	xmax = 1080;
	ymax = 1080;
	data.win_size_max = xmax;
	data.win_size_min = 0;
	data.offset_x = 0;
	data.offset_y = 0;
	if (mlx_init_protected(&data) != 0)
		return (-1);
	printf("Hello Nana_ïs\n");
	while (y <= ymax)
	{
		x = 0;
		while (x <= xmax)
		{
			new_x = scaling_x(&data, (double)x, SIZE_W);
			new_y = scaling_y(&data, (double)y, SIZE_H);
			my_mlx_pixel_put(&data, x, y, 0x00ff0000);
			x++;
		}
		y++;
		sleep(1);
		printf("new_y = %f \n", new_y);
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
	mlx_put_image_to_window(data.mlx, data.win, data.img, 0, 0);
	mlx_mouse_hook(data.win, mouse_click, &data);
	mlx_hook(data.win, 2, 1L << 0, kb_event, &data);
	mlx_hook(data.win, 17, 0L, mlx_loop_end, data.mlx);
	mlx_loop(data.mlx);
	mlx_destroy_all(&data);
	return (0);
}
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
