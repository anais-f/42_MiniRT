#include "miniRT.h"
#include "camera.h"
#include "display_mlx.h"

static void	calc_pixel_and_check_obj(t_minirt *minirt, t_hit *hit, int x, int y)
{
	size_t	i;
	double	dst;

	ft_memset(hit, 0, sizeof(t_hit));
	hit->dst = -1;
	hit->ray = create_ray_from_cam(minirt, x, y);
	hit->ray.direction = normalize_vec3(\
			mult_vec3_matrix(hit->ray.direction, minirt->cam.rotation_matrix));
	i = 0;
	while (i < minirt->objects.size)
	{
		dst = object_intersection(hit->ray, *minirt->objects.array[i]);
		if (dst != -1 && (dst < hit->dst || hit->dst == -1))
		{
			hit->dst = dst;
			hit->object = *minirt->objects.array[i];
		}
		i++;
	}
}

void	render_scene(t_minirt *minirt, t_img *img)
{
	int		x;
	int		y;
	t_hit	hit;

	y = 0;
	while (y <= HEIGHT_WIN)
	{
		x = 0;
		while (x <= WIDTH_WIN)
		{
			calc_pixel_and_check_obj(minirt, &hit, x, y);
			hit_point(minirt, hit.ray, &hit);
			minirt->color = get_color_pixel(minirt, hit);
			my_mlx_pixel_put(img, x, y, minirt->color.color);
			x++;
		}
		y++;
	}
	printf("Render done\n");
}
