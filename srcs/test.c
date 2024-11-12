#include "miniRT.h"
#include "libft.h"
#include "display_mlx.h"



int test(t_img *img)
{
	int y = 0;
	int x = 0;
	int	i_width = WIDTH_WIN;
	int	i_height = HEIGHT_WIN; // WIDTH_WIN / img->ratio; a check si bien > 1
	t_color color;

	while (y <= i_height)
	{
		x = 0;
		while (x <= i_width)
		{
			color.r = (float)x / ((float)i_width - 1) * (float)255;
			color.g = (float)y / ((float)i_height - 1) * (float)255;
			color.b = 0.0;
			color.a = 0.0;

			my_mlx_pixel_put(img, x, y, color.color);
			x++;
		}
		y++;
	}
	return (0);
}


