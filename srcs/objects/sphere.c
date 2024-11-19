#include "miniRT.h"



float	sphere_intersection(t_minirt *minirt, t_ray ray, t_object sphere)
{
	(void)minirt;
	/**********************************  creation des rayons depuis la caméra ******************************/

	
	t_vec3 offset_ray_origin = sub_vec3(ray.origin, sphere.position); // vecteur entre le point d'origine et le centre de la sphere

	

	/************************************equation d'intersection de sphere, abc = l sphere *********************************/

	//(bx^2 +by^2)t^2 + (2bxax + 2byay)t + (ax^2 + ay^2 - r^2) = 0 -> resolution de l'equation avec a, b et c chaque composant de l'equation
	// t = la distance entre le point d'origine et le point d'intersection
	// a = origine du rayon
	// b = la direction du rayon
	// r = rayon de la sphere

	float a = dot_vec3(ray.direction, ray.direction); 
	float b = 2.0f * dot_vec3(offset_ray_origin, ray.direction); // ou off set ray origin / ray.origin ?
	float c = dot_vec3(offset_ray_origin, offset_ray_origin) - sphere.spec.sphere.radius * sphere.spec.sphere.radius;
	float discriminant = b * b - 4.0f * a * c;

	if (discriminant >= 0.f) // colorisation de la scene
	{
		float t0 = (-b - sqrt(discriminant)) / (2.0f * a); // calcul de la distance entre le point d'origine et le point d'intersection
		float t1 = (-b + sqrt(discriminant)) / (2.0f * a);
		if (t0 < 0) // je checke si je suis dans la sphere et je prends la distance la plus proche
			t0 = t1;
		if (t0 < 0) // je checke si l'objet n'est pas derriere la camera
			return (-1);
		return (t0); //retourne la distance entre le point d'origine et le point d'intersection
	}
	return (-1);
}

float	object_intersection(t_minirt *minirt, t_ray ray, t_object object)
{
	if (object.type == SPHERE)
		return (sphere_intersection(minirt, ray, object));
	if (object.type == PLANE)
		return (plane_intersection(minirt, ray, object));
	if (object.type == CYLINDER)	
		return (cylinder_intersection(minirt, ray, object));
	return (-1);
}		


