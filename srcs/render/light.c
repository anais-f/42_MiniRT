#include "miniRT.h"
#include <float.h>
# define EPSILON 1e-5

t_vec3 get_ambient_light(t_minirt *minirt) // a faire dans le parsing
{
	t_vec3 ambient_light;

	ambient_light = color_to_vec3(minirt->ambient_light.color);
	ambient_light = mult_nb_vec3(ambient_light, minirt->ambient_light.brightness);
	return (ambient_light);
}


/*
Ajout d'un "bias" à l'origine du rayon : 
J'ai ajouté un petit décalage (bias) à l'origine du rayon en utilisant la normale de la surface à la position de l'impact (hit.normal). 
Cela garantit que le rayon ne commence pas à l'exact endroit où il pourrait interagir avec la surface de l'objet de manière erronée. 
Le vec3_add(ray.origin, vec3_multiply(hit.normal, EPSILON)) déplace légèrement l'origine du rayon dans la direction de la normale, 
évitant ainsi de fausses intersections dues à des problèmes de précision.

ou utiliser le ray.direction * - 1 au lieu de hit.normal
*/
bool	check_ray_to_light(t_minirt *minirt, t_hit hit, t_vec3 light_dir)
{
	t_ray	ray;
	float	t;
	int i = 0;

	ray.origin = hit.position;
	ray.direction = light_dir;
	ray.origin = add_vec3(ray.origin, mult_nb_vec3(hit.ray.direction, -EPSILON)); 

	while (i < 4)
	{
		//printf("float = %f\n", object_intersection(minirt, ray, minirt->object[i]));
		t = object_intersection(minirt, ray, minirt->object[i]);
		if ((t > EPSILON))
			return (false);
		i++;
	}
	return (true);
}


/* calcul du ratio de brightness de la lumiere directionnelle */
float	calcul_light_bright(t_minirt *minirt, t_hit hit)
{
	t_vec3	light_dir;
	float	light_intensity;

	light_dir = sub_vec3(hit.position, minirt->light.position); // calcul de la direction de la lumiere
	light_dir = mult_nb_vec3(light_dir, -1.0f * (minirt->light.brightness)); // inversion de la direction de la lumiere pour aller de nous a la lumiere et pas le contraire
	light_dir = normalize_vec3(light_dir);
	light_intensity = dot_vec3(hit.normal, light_dir); // calcul de la lumiere, == cos(angle)
	if (light_intensity < 0.0f) // on ne veut pas de valeur negative, c'est le plus grand entre 0 et la lumiere
	{
		light_intensity = 0.0f;
		return (light_intensity);
	}

	if (check_ray_to_light(minirt, hit, light_dir) == false)
	{
		light_intensity = 0.0f;
		return (light_intensity);
	}
	return (light_intensity);
}

t_color	get_color_pixel(t_minirt *minirt, t_hit hit)
{
	t_vec3	ambient_light;
	t_vec3	light_color;
	t_color final_color;
	float 	light_bright;

	if (hit.dst == -1)
		return (t_color) {0xFF000000};
	ambient_light = get_ambient_light(minirt);
	light_bright = calcul_light_bright(minirt, hit); // sera a 0 si j'ai une intersection entre la lumiere et l'objet
	light_color = color_to_vec3(minirt->light.color);
	light_color = mult_nb_vec3(light_color, light_bright);
	light_color = add_color_vec3(light_color, ambient_light);
	light_color.x *= (color_to_vec3(hit.object.color)).x;
	light_color.y *= (color_to_vec3(hit.object.color)).y;
	light_color.z *= (color_to_vec3(hit.object.color)).z;
	final_color = vec3_to_color(light_color);
	return (final_color);
}

/*
void	get_color_pixel(t_minirt *minirt, t_hit hit)
{
	t_vec3	ambient_light;
	t_vec3	light_color;
	t_color final_color;
	float 	light_bright;

	if (hit.dst == -1)
		return ;
	ambient_light = get_ambient_light(minirt);
	light_bright = calcul_light_bright(minirt, hit); // sera a 0 si j'ai une intersection entre la lumiere et l'objet
	light_color = color_to_vec3(minirt->light.color);
	light_color = mult_nb_vec3(light_color, light_bright);
	light_color = add_color_vec3(light_color, ambient_light);
	light_color.x *= (color_to_vec3(hit.object.color)).x;
	light_color.y *= (color_to_vec3(hit.object.color)).y;
	light_color.z *= (color_to_vec3(hit.object.color)).z;
	final_color = vec3_to_color(light_color);
	minirt->color = final_color;
	return (final_color);
}
*/