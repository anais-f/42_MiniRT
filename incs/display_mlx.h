#ifndef DISPLAY_MLX_H
# define DISPLAY_MLX_H

# define HEIGHT_WIN 540 /* HEIGHT of MLX WIN */
# define WIDTH_WIN 720 /* WIDTH of MLX WIN */
# define ESC_KB 65307 /* ESC BUTTON */
# define LEFT_KB 65361 /* LEFT BUTTON */
# define RIGHT_KB 65363 /* RIGHT BUTTON */
# define UP_KB 65362 /* UP BUTTON */
# define DOWN_KB 65364 /* DOWN BUTTON */
# define W_KB 119 /* W BUTTON */
# define A_KB 97 /* A BUTTON */
# define S_KB 115 /* S BUTTON */
# define D_KB 100 /* D BUTTON */
# define R_KB 114 /* R BUTTON */
# define F_KB 102 /* F BUTTON */

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