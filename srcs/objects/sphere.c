#include "miniRT.h"

int	display_sphere(t_minirt *minirt, int x, int y, int i)
{
	(void)x, (void)y, (void)minirt;
	// printf("cam ratio = %f et fov = %f\n", minirt->cam.ratio, minirt->cam.FOV);
	//t_vec3 light_dir = normalize_vec3((t_vec3){1.0f, 1.0f, -1.0f}); // direction de la lumiere


	/******************* conversion des x et y de pixel sur un range [-1;1] et conserver le ratio de l'écran*****************/
	t_vec2 coord;
	coord.x = (float)x / (float)WIDTH_WIN * 2.0f - 1.0f;
	coord.x *= minirt->cam.ratio;
	coord.y = -((float)y / (float)HEIGHT_WIN * 2.0f - 1.0f);
	

	/**********************************  creation des rayons depuis la caméra ******************************/
	t_ray ray;
	ray.origin = minirt->cam.position;
	ray.direction = (t_vec3){coord.x, coord.y, minirt->cam.direction.z}; // direction du rayon
	//ray.direction = normalize_vec3(ray.direction);
	
	
	t_vec3 offset_ray_origin = sub_vec3(ray.origin, minirt->object[i].position); // vecteur entre le point d'origine et le centre de la sphere

	

	/************************************equation d'intersection de sphere, abc = l sphere *********************************/

	//(bx^2 +by^2)t^2 + (2bxax + 2byay)t + (ax^2 + ay^2 - r^2) = 0 -> resolution de l'equation avec a, b et c chaque composant de l'equation
	// t = la distance entre le point d'origine et le point d'intersection
	// a = origine du rayon
	// b = la direction du rayon
	// r = rayon de la sphere

	float a = dot_vec3(ray.direction, ray.direction); 
	float b = 2.0f * dot_vec3(offset_ray_origin, ray.direction); // ou off set ray origin / ray.origin ?
	float c = dot_vec3(offset_ray_origin, offset_ray_origin) - minirt->object[i].spec.sphere.radius * minirt->object[i].spec.sphere.radius;
	float discriminant = b * b - 4.0f * a * c;

	if (discriminant >= 0.f) // colorisation de la scene
	{
		float t0 = (-b - sqrt(discriminant)) / (2.0f * a); // calcul de la distance entre le point d'origine et le point d'intersection
		float t1 = (-b + sqrt(discriminant)) / (2.0f * a);
		if (t0 < 0) // je checke si je suis dans la sphere et je prends la distance la plus proche
			t0 = t1;
		if (t0 < 0) // je checke si l'objet n'est pas derriere la camera
			return (-1);


		/******************************* chercher le point d'intersection**************************************/
		t_vec3 hit_position = add_vec3(ray.origin, mult_nb_vec3(ray.direction, t0)); // point d'impact
		t_vec3 normal = normalize_vec3(sub_vec3(hit_position, minirt->object[i].position)); // normalisation du vecteur - A REVOIR

		t_vec3 sphere_in = sub_vec3(minirt->cam.position, minirt->object[i].position);
		if (dot_vec3(sphere_in, sphere_in) <= minirt->object[i].spec.sphere.radius) // test si on est a l'interieur de la sphere
		{
			printf("HERE\n");
			normal = mult_nb_vec3(normal, -1.0f); // inversion de la normal si on est a l'interieur de la sphere
		}


		/********************************************* gestion lumiere ********************************************/
		
		t_vec3 light_dir = normalize_vec3(sub_vec3(hit_position, minirt->light.position)); // calcul de la direction de la lumiere
		light_dir = mult_nb_vec3(light_dir, -1.0f); // inversion de la direction de la lumiere pour aller de nous a la lumiere et pas le contraire
		float light = dot_vec3(normal, light_dir); // calcul de la lumiere, == cos(angle)
		if (light < 0.0f) // on ne veut pas de valeur negative, c'est le plus grand entre 0 et la lumiere
			light = 0.0f;


		/***************************************** gestion de la couleur ****************************************/
		minirt->color.r = minirt->object[i].color.r * light;
		minirt->color.g = minirt->object[i].color.g * light;
		minirt->color.b = minirt->object[i].color.b * light;
		minirt->color.a = 0;

		return (t0); //retourne la distance entre le point d'origine et le point d'intersection
	}
	// else // remplissage de l'image, de la couleur du pixel, a ressortir dans render ?
	// {
	// 	minirt->color.r = 0;
	// 	minirt->color.g = 0;
	// 	minirt->color.b = 0;
	// 	minirt->color.a = 0;
	// }
	return (-1);
}

/*

equation de cercle = (x-a)^2 + (y-b)^2 - r^2 = 0






*/

