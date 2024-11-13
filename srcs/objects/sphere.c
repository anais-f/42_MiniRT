#include "miniRT.h"

void	display_sphere(t_minirt *minirt, int x, int y)
{

	(void)x, (void)y, (void)minirt;
	// printf("cam ratio = %f et fov = %f\n", minirt->cam.ratio, minirt->cam.FOV);
	t_vec2 coord;
	t_vec3 light_dir = normalize_vec3((t_vec3){1.0f, 1.f, -1.f}); // direction de la lumiere

	coord.x = (float)x / (float)WIDTH_WIN * 2.0f - 1.0f;
	coord.x *= minirt->cam.ratio; // permet de garder le ratio de l'ecran
	coord.y = (float)y / (float)HEIGHT_WIN * 2.0f - 1.0f;
	
	t_vec3 ray_dir = {coord.x, coord.y, -1.0f};
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
		//printf("light = %f\n", light);

		minirt->color.r = 0 * light;
		minirt->color.g = 205 * light;
		minirt->color.b = 205 * light;
		minirt->color.a = 0;
	}
	else
	{
		minirt->color.r = 0;
		minirt->color.g = 0;
		minirt->color.b = 0;
		minirt->color.a = 0;
	}
}
