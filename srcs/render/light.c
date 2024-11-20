#include "miniRT.h"

void get_ambient_light(t_minirt *minirt) // a faire dans le parsing
{
	color_to_vec3(&minirt->ambient_light.color);


	// minirt->ambient_light.color.r *= minirt->ambient_light.brightness;
	// minirt->ambient_light.color.g *= minirt->ambient_light.brightness;
	// minirt->ambient_light.color.b *= minirt->ambient_light.brightness;
}

/* calcul du ratio de brightness de la lumiere directionnelle */
float	calcul_light_ratio(t_minirt *minirt, t_hit hit)
{
	t_vec3 light_dir;
	float light_intensity;

	light_dir = normalize_vec3(sub_vec3(hit.position, minirt->light.position)); // calcul de la direction de la lumiere
	light_dir = mult_nb_vec3(light_dir, -1.0f); // inversion de la direction de la lumiere pour aller de nous a la lumiere et pas le contraire
	light_intensity = dot_vec3(hit.normal, light_dir); // calcul de la lumiere, == cos(angle)
	if (light_intensity < 0.0f) // on ne veut pas de valeur negative, c'est le plus grand entre 0 et la lumiere
		light_intensity = 0.0f;
	light_intensity *= minirt->light.brightness; // on multiplie par la brightness de la lumiere
	return (light_intensity);
}

t_color	get_color_object_pixel(t_minirt *minirt, t_hit hit)
{
	t_color light_color;
	float 	light_ratio;

	if (hit.dst == -1)
		return (t_color){0};
	light_ratio = calcul_light_ratio(minirt, hit);
	light_color = multiply_color_float(minirt->light.color, light_ratio);

	light_color = add_colors(minirt->ambient_light.color, light_color);

	//return (multiply_color_float(hit.object.color, light_ratio));
//	return (multiply_colors(light_color, hit.object.color));
//	return (light_color);
	//return (multiply_colors(minirt->ambient_light.color, hit.object.color));
}

/*
	t_color light_color;
	t_color final_color;
	float 	light_ratio;

	if (hit.dst == -1)
		return (t_color){0};
	light_ratio = calcul_light_ratio(minirt, hit);
	light_color = multiply_color_float(minirt->light.color, light_ratio); // calcul lumiere ponctuelle

	final_color = add_colors(light_color, minirt->ambient_light.color); // calcul lumiere ambiante
	final_color = multiply_colors(final_color, hit.object.color); // calcul couleur de l'objet

	return (final_color);*/