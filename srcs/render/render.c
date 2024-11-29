#include "miniRT.h"
#include "camera.h"
#include "display_mlx.h"

void	render_scene(t_minirt *minirt, t_img *img)
{
	int		x;
	int		y;
	size_t	i;
	double	dst;
	t_ray	ray; // tableau de rayons a la place de la creation des rayons
	t_hit	hit;
	

	// printf("D = %f\n", tan(minirt->cam.FOV * 0.5) * 2);

	y = 0;
	while (y <= HEIGHT_WIN)
	{
		x = 0;
		while (x <= WIDTH_WIN)
		{
			
			// on va afficher l'objet le plus proche en premier
			ft_memset(&hit, 0, sizeof(t_hit));
			hit.dst = -1;


			ray = create_ray_from_cam(minirt, x, y); // ray cree en 0.0.0 et dir 0.0.1

			// if ((x == 0 || x == WIDTH_WIN - 1) && (y == 0 || y == HEIGHT_WIN - 1))
			// 	printf("ray direction (%f, %f, %f)\n", ray.direction.x, ray.direction.y, -ray.direction.z);

			t_vec3 tmp = mult_vec3_matrix((t_vec3){0,0,1}, minirt->cam.rotation_matrix);
			// printf("mult vec3 matrix vec.x = %f, vec.y = %f, vec.z = %f\n", tmp.x, tmp.y, tmp.z);
			// printf("mult vec3 matrix vec.x = %f, vec.y = %f, vec.z = %f\n\n", normalize_vec3(minirt->cam.direction).x, normalize_vec3(minirt->cam.direction).y, normalize_vec3(minirt->cam.direction).z);
			ray.direction = normalize_vec3(mult_vec3_matrix(ray.direction, minirt->cam.rotation_matrix));

			// a la place de la creation des rayons, j'ai la transformation des rayons (rotation+translation)


			hit.ray = ray; // pour recuperer le ray pour le calcul de l'ombre et le point de depart de l'intersection
			i = 0;
			while (i < minirt->objects.size)
			{
				// trouver l'objet le plus proche -> recuperer la distance
				dst = object_intersection(ray, *minirt->objects.array[i]); // renvoi un double pour faire le calcul pour trouver l'objet le plus proche 
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


/*
je cree les rayons via l'origine 0.0.0 et direction 0.0.1 pour faire les calculs de la matrice simplement
je fais tous les calculs pour avoir la matrice de rotation et de translation
une fois que j'ai la matrice, je la multiplie avec les rayons pour les transformer en repartant de l'origine de la camera

1 - je calcule le acos de axe y et axe x (faire un tvec2 pour plus de lisibilite)
axe y je prends x et z de direction monde (0.0.1) et x et z de direction camera
axe x je prends y et z de direction monde (0.0.1) et y et z de direction camera
le calcul de acos me donne l'angle theta deja en radians
je fais ensuite le sinus pour avoir le sens positifi ou negatif de la rotation

creer une matrice de rotation 3x3 avec un double tableau de 3*3

*/