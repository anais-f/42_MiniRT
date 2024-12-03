#include "miniRT.h"
#include "camera.h"

void	render_scene(t_minirt *minirt, t_img *img)
{
	int		x;
	int		y;
	size_t	i;
	double	dst;
	t_ray	ray; // tableau de rayons a la place de la creation des rayons
	t_hit	hit;

	//calcul de la matrice de transformation des rayons de la camera
	// matrix = matrix_x * natrix_y
	y = 0;
	while (y <= HEIGHT_WIN)
	{
		x = 0;
		while (x <= WIDTH_WIN)
		{
			// on va afficher l'objet le plus proche en premier
			ft_memset(&hit, 0, sizeof(t_hit));
			hit.dst = -1;

			ray = create_ray_from_cam(minirt, x, y);
			// ray = mult_matrix(rays[y][x], matrix)
			// a la place de la creation des rayons, j'ai la transformation des rayons (rotation+translation)

			hit.ray = ray; // pour recuperer le ray pour le calcul de l'ombre
			i = 0;
			while (i < minirt->objects.size)
			{
				// trouver l'objet le plus proche -> recuperer la distance
				dst = object_intersection(ray, *minirt->objects.array[i], &hit); // renvoi un double pour faire le calcul pour trouver l'objet le plus proche 
				if (dst != -1 && (dst < hit.dst || hit.dst == -1))
				{
					hit.dst = dst;
					hit.object = *minirt->objects.array[i];
				}
				i++;
			}
			hit_point(minirt, ray, &hit); // calculer mon intersection et la normale
			minirt->color = get_color_pixel(minirt, hit);// calculer la couleur du pixel
			my_mlx_pixel_put(img, x, y, minirt->color.color);
			x++;
		}
		y++;
	}
	printf("Render done\n");
}
