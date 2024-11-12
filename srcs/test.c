#include "miniRT.h"
#include "libft.h"
#include "display_mlx.h"



int test(t_img *img)
{
	int y = 0;
	int x = 0;
	int	i_width = WIDTH_WIN;
	int	i_height = HEIGHT_WIN;
	int r, g, b;

	while (y <= i_height)
	{
		x = 0;
		while (x <= i_width)
		{
			r = (float)x / ((float)i_width - 1) * (float)255;
			g = (float)y / ((float)i_height - 1) * (float)255;
			b = 0.0;

			int color = (r << 16) + (g << 8) + b; // int 32 bit avec 8 ppour a et 8 pour chaque -> bitshift pour placer la couleur au bon endroit
			my_mlx_pixel_put(img, x, y, color);
			x++;
		}
		y++;
	}
	return (0);
}

