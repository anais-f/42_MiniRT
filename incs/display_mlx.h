#ifndef DISPLAY_MLX_H
# define DISPLAY_MLX_H

# define HEIGHT_WIN 720 /* HEIGHT of MLX WIN */
# define WIDTH_WIN 720 /* WIDTH of MLX WIN */
# define ESC_KB 65307 /* ESC BUTTON */

# include <mlx.h>
# include <stdlib.h>

typedef struct s_img
{
	void	*img;
	void	*mlx_ptr;
	void	*win_ptr;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_img;

int		mlx_init_protected(t_img *img);
void	my_mlx_pixel_put(t_img *img, int x, int y, int color);
void	mlx_launch_event_and_loop(t_img *img);
void	mlx_destroy_all(t_img *img);




#endif	