#include "miniRT.h"

float	sphere_intersection(t_minirt *minirt, t_ray ray, t_object sphere)
{
	(void)minirt;
	/***** a voir  *****/
	t_vec3 offset_ray_origin = sub_vec3(ray.origin, sphere.position); // vecteur entre le point d'origine et le centre de la sphere


	float a = dot_vec3(ray.direction, ray.direction); 
	float b = 2.0f * dot_vec3(offset_ray_origin, ray.direction); // ou off set ray origin / ray.origin ?
	float c = dot_vec3(offset_ray_origin, offset_ray_origin) - sphere.spec.sphere.radius * sphere.spec.sphere.radius;
	float discriminant = b * b - 4.0f * a * c;
	if (discriminant < 0.f) 
		return (-1);
	// colorisation de la scene
	float t0 = (-b - sqrt(discriminant)) / (2.0f * a); // calcul de la distance entre le point d'origine et le point d'intersection
	float t1 = (-b + sqrt(discriminant)) / (2.0f * a);
	if (t0 < 0) // je checke si je suis dans la sphere et je prends la distance la plus proche
		t0 = t1;
	if (t0 < 0) // je checke si l'objet n'est pas derriere la camera
		return (-1);
	return (t0); //retourne la distance entre le point d'origine et le point d'intersection
}
	//(bx^2 +by^2)t^2 + (2bxax + 2byay)t + (ax^2 + ay^2 - r^2) = 0 -> resolution de l'equation avec a, b et c chaque composant de l'equation
	// t = la distance entre le point d'origine et le point d'intersection
	// a = origine du rayon
	// b = la direction du rayon
	// r = rayon de la sphere

t_vec3	get_normal_sphere(t_minirt *minirt, t_hit hit)
{
	t_vec3 normal;
	t_vec3 sphere_in;
	
	normal = normalize_vec3(sub_vec3(hit.position, hit.object.position));
	sphere_in = sub_vec3(minirt->cam.position, hit.object.position);
	if (dot_vec3(sphere_in, sphere_in) <= hit.object.spec.sphere.radius) // test si on est a l'interieur de la sphere
	{
	//	printf("HERE\n");
		normal = mult_nb_vec3(normal, -1.0f); // inversion de la normal si on est a l'interieur de la sphere
	}
	return (normal);
}	


