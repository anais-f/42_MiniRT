#include "miniRT.h"
#include "libft.h"
#include "display_mlx.h"
#include "camera.h"


t_ray create_ray(t_camera cam, t_vec2 coord)
{
	t_ray ray;

	ray.origin = cam.position;

	ray.direction = cam.direction;


	float fov_scale = tan(cam.FOV * 0.5); // a mettre dans t_camera

	/* ray */

	coord.px = (2 * (coord.px + 0.5) / (float)WIDTH_WIN - 1) * cam.ratio * fov_scale;
	coord.py = (1 - 2 * (coord.py + 0.5) / (float)HEIGHT_WIN) * fov_scale;


	return (ray);
}

int test(t_img *img)
{
	int x = 0;
	int y = 0;
	t_vec2 coord;
	t_color color;
	t_camera cam;

	coord.px = 0;
	coord.py = 0;


	/* camera */
	// cam.position = (t_vec3){0, 0, 0};
	// cam.direction = (t_vec3){0, 0, -1};
	// cam.FOV = 60 * M_PI / 180;
	cam.ratio = (float)WIDTH_WIN / (float)HEIGHT_WIN;
	// printf("cam FOV = %f\n", cam.FOV);

	
	/* render */		
	while (y <= HEIGHT_WIN)
	{
		x = 0;
		while (x <= WIDTH_WIN)
		{
			t_vec3 light_dir = normalize_vec3((t_vec3){1.0f, 1.f, -1.f}); // direction de la lumiere
			coord.px = (float)x / (float)WIDTH_WIN * 2.0f - 1.0f;
			coord.px *= cam.ratio; // permet de garder le ratio de l'ecran
			coord.py = (float)y / (float)HEIGHT_WIN * 2.0f - 1.0f;
			
			t_vec3 ray_dir = {coord.px, coord.py, -1.0f};
			ray_dir = normalize_vec3(ray_dir);
			t_vec3 ray_origin = {0.f, 0.f, 2.f};
			float radius = 1.0f;

			/*equation d'intersection de sphere, abc = l sphere */
			//(bx^2 +by^2)t^2 + 2(bxax + byay)t + (ax^2 + ay^2 - c^2) = 0 -> resolution de l'equation avec a, b et c
			float a = dot_vec3(ray_dir, ray_dir);
			float b = 2.0f * dot_vec3(ray_origin, ray_dir);
			float c = dot_vec3(ray_origin, ray_origin) - radius * radius;
			float discriminant = b * b - 4.0f * a * c;

			if (discriminant >= 0.f)
			{
				float t0 = (-b - sqrt(discriminant)) / (2.0f * a); // calcul de la distance entre le point d'origine et le point d'intersection
				float t1 = (-b + sqrt(discriminant)) / (2.0f * a);

				if (t0 < 0)
					t0 = t1;

				t_vec3 hitPosition = add_vec3(ray_origin, mult_nb_vec3(ray_dir, t0)); // poitn d'impact
				t_vec3 normal = normalize_vec3(sub_vec3(hitPosition, (t_vec3){0.f, 0.f, 0.f})); // normalisation du vecteur

				light_dir = mult_nb_vec3(light_dir, -1.0f); // inversion de la direction de la lumiere	
				float light = dot_vec3(normal, light_dir); // calcul de la lumiere
				if (light < 0)
					light = 0;
				printf("light = %f\n", light);

				color.r = 255 * light;
				color.g = 0 * light;
				color.b = 205 * light;
				color.a = 0;
			}
			else
			{
				color.r = 0;
				color.g = 0;
				color.b = 0;
				color.a = 0;
			}

			my_mlx_pixel_put(img, x, y, color.color);

			x++;
		}
		y++;
	}
	return (0);
}


// verifier que l'angle de la lumiere n'est pas sup a 180 degres et pas inferieur a 0
// verifier que t0 n;''est pas negatif sinon ne pas l'afficher car derriere la camera
// t1 n'est utile que si on est dans la sphere

