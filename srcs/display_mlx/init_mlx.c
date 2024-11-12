#include "display_mlx.h"
# include "libft.h"

int	mlx_init_protected(t_img *img)
{
	ft_bzero(img, sizeof(t_img)); //effacer l'image pour redessiner dessus
	// fonction pour init la structure si on ajoute des donnees?
	img->ratio = (float)WIDTH_WIN / (float)HEIGHT_WIN;

	img->mlx_ptr = mlx_init();
	if (!img->mlx_ptr)
		return (-1);
	img->win_ptr = mlx_new_window(img->mlx_ptr, WIDTH_WIN, HEIGHT_WIN, "miniRT");
	img->img = mlx_new_image(img->mlx_ptr, WIDTH_WIN, HEIGHT_WIN);
	if (!img->win_ptr || !img->img)
	{
		mlx_destroy_all(img);
		return (-1);
	}
	img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel,
			&img->line_length, &img->endian);
	return (0);
}
