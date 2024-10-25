#include "miniRT.h"
#include "libft.h"

typedef struct s_data
{
	void			*img;
	void			*mlx;
	void			*win;
	char			*addr;
	int				bits_per_pixel;
	int				line_length;
	int				endian;
}				t_data;


int	kb_event(int keycode, t_data *data)
{
	if (keycode == ESC_KB)
		mlx_loop_end(data->mlx);
	return (0);
}

void	mlx_destroy_all(t_data *data)
{
	if (data->img)
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


int test(void)
{
	t_data	data;
	int y;
	int x;
	int	xmax;
	int	ymax;

	x = 0;
	y = 0;
	xmax = 1080;
	ymax = 1080;
	if (mlx_init_protected(&data) != 0)
		return (-1);
	printf("Hello Nana_ïs\n");
	while (y <= ymax)
	{
		x = 0;
		while (x <= xmax)
		{
			my_mlx_pixel_put(&data, x, y, 0x00FF00F0);
			x++;
		}
		y++;
	}
	int cx = 540; // Centre en x (coordonnée centrale)
	int cy = 540; // Centre en y (coordonnée centrale)
	int r = 100;  // Rayon du cercle
	//int lx = 440; // Position x de la lumière
	//int ly = 440; // Position y de la lumière

	y = cy - r;
	while (y <= cy + r)
	{
		x = cx - r;
		while (x <= cx + r)
		{
			// Calculer si le point est à l'intérieur du cercle (surface de la sphère)
			int dx = x - cx; // = (x - decalage)
			int dy = y - cy; // = (y - decalage)
			if (dx * dx + dy * dy <= r * r) // equation cercle 
			{
				// Calculer la normale au point (x, y)
				// float nx = dx / (float)r;
				// float ny = dy / (float)r;

				// Calculer la direction de la lumière
				// float lx_norm = (lx - x) / (float)r;
				// float ly_norm = (ly - y) / (float)r;

				// Calculer l'intensité de la lumière en fonction de la normale
				// float dot_product = (nx * lx_norm + ny * ly_norm);
				// float intensity = fmax(0, dot_product); // L'intensité est comprise entre 0 et 1

				// Couleur avec dégradé (0xFFFFFF est blanc pur, multiplié par l'intensité)
				// int color = (int)(intensity * 255) << 16 | (int)(intensity * 255) << 8 | (int)(intensity * 255);

				// Dessiner le pixel avec la couleur calculée
				my_mlx_pixel_put(&data, x, y, 0x00000000); //color
			}
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(data.mlx, data.win, data.img, 0, 0);
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