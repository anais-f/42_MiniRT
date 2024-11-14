#include "miniRT.h"

void	display_sphere(t_minirt *minirt, int x, int y)
{
	(void)x, (void)y, (void)minirt;
	// printf("cam ratio = %f et fov = %f\n", minirt->cam.ratio, minirt->cam.FOV);
	//t_vec3 light_dir = normalize_vec3((t_vec3){1.0f, 1.0f, -1.0f}); // direction de la lumiere


	/* conversion des x et y de pixel sur un range [-1;1] et conserver le ratio de l'écran*/
	t_vec2 coord;
	coord.x = (float)x / (float)WIDTH_WIN * 2.0f - 1.0f;
	coord.x *= minirt->cam.ratio * - 1.0f;
	coord.y = (float)y / (float)HEIGHT_WIN * 2.0f - 1.0f;
	

	/* lancé des rayons depuis la caméra */
	t_vec3 ray_origin = minirt->cam.position;
	t_vec3 ray_dir = {coord.x, coord.y, -1.0f};
	ray_dir = normalize_vec3(ray_dir);

	

	/*equation d'intersection de sphere, abc = l sphere */
	//(bx^2 +by^2)t^2 + 2(bxax + byay)t + (ax^2 + ay^2 - c^2) = 0 -> resolution de l'equation avec a, b et c
	float a = dot_vec3(ray_dir, ray_dir);
	float b = 2.0f * dot_vec3(ray_origin, ray_dir);
	float c = dot_vec3(ray_origin, ray_origin) - minirt->object.spec.sphere.radius * minirt->object.spec.sphere.radius;
	float discriminant = b * b - 4.0f * a * c;

	if (discriminant >= 0.f) // colorisation de la scene
	{
		float t0 = (-b - sqrt(discriminant)) / (2.0f * a); // calcul de la distance entre le point d'origine et le point d'intersection
		float t1 = (-b + sqrt(discriminant)) / (2.0f * a);
		if (t0 < 0)
			t0 = t1;

		/* chercher le point d'intersection*/
		t_vec3 hitPosition = add_vec3(ray_origin, mult_nb_vec3(ray_dir, t0)); // point d'impact
		t_vec3 normal = normalize_vec3(sub_vec3(hitPosition, minirt->object.position)); // normalisation du vecteur - A REVOIR

		/* gestion lumiere */
		t_vec3 light_dir = normalize_vec3(sub_vec3(minirt->light.position, hitPosition)); // calcul de la direction de la lumiere
	//	light_dir = mult_nb_vec3(light_dir, -1.0f); // inversion de la direction de la lumiere (et necessite d'inverser la sub au dessus)
		float light = dot_vec3(normal, light_dir); // calcul de la lumiere
		if (light < 0)
			light = 0;
		//printf("vecteur direction lumiere = %f %f %f\n", light_dir.x, light_dir.y, light_dir.z);	

		/* gestion de la couleur */
		minirt->color.r = minirt->object.color.r * light;
		minirt->color.g = minirt->object.color.g * light;
		minirt->color.b = minirt->object.color.b * light;
		minirt->color.a = 0;

	}
	else // remplissage de l'image, de la couleur du pixel, a ressortir dans render ?
	{
		minirt->color.r = 0;
		minirt->color.g = 0;
		minirt->color.b = 0;
		minirt->color.a = 0;
	}
}
