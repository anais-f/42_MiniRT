#include "miniRT.h"

t_vec3 get_ambient_light(t_minirt *minirt) // a faire dans le parsing
{
	t_vec3 ambient_light;

	ambient_light = color_to_vec3(minirt->ambient_light.color);
	mult_nb_vec3(ambient_light, minirt->ambient_light.brightness);
	return (ambient_light);
}

/* calcul du ratio de brightness de la lumiere directionnelle */
float	calcul_light_bright(t_minirt *minirt, t_hit hit)
{
	t_vec3 light_dir;
	float light_intensity;

	light_dir = normalize_vec3(sub_vec3(hit.position, minirt->light.position)); // calcul de la direction de la lumiere
	light_dir = mult_nb_vec3(light_dir, -1.0f * (minirt->light.brightness)); // inversion de la direction de la lumiere pour aller de nous a la lumiere et pas le contraire
	light_intensity = dot_vec3(hit.normal, light_dir); // calcul de la lumiere, == cos(angle)
	if (light_intensity < 0.0f) // on ne veut pas de valeur negative, c'est le plus grand entre 0 et la lumiere
		light_intensity = 0.0f;
	return (light_intensity);
}

t_color	get_color_object_pixel(t_minirt *minirt, t_hit hit)
{
	t_vec3	ambient_light;
	t_vec3	light_color;
	t_color final_color;
	float 	light_bright;

	if (hit.dst == -1)
		return (t_color){0};
	ambient_light = get_ambient_light(minirt);
	light_bright = calcul_light_bright(minirt, hit);
	light_color = color_to_vec3(minirt->light.color);
	light_color = mult_nb_vec3(light_color, light_bright);
	light_color = add_vec3(light_color, ambient_light);
	light_color.x *= (color_to_vec3(hit.object.color)).x;
	light_color.y *= (color_to_vec3(hit.object.color)).y;
	light_color.z *= (color_to_vec3(hit.object.color)).z;
	final_color = vec3_to_color(light_color);
	return (final_color);
}