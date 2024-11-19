#include "miniRT.h"

void get_ambient_light(t_minirt *minirt)
{
	float r;
	float g;
	float b;

	r = minirt->ambient_light.color.r / 255.f * minirt->ambient_light.brightness;
	g = minirt->ambient_light.color.g / 255.f * minirt->ambient_light.brightness;
	b = minirt->ambient_light.color.b / 255.f * minirt->ambient_light.brightness;
	minirt->ambient_light.color.r = r * 255;
	minirt->ambient_light.color.g = g * 255;
	minirt->ambient_light.color.b = b * 255;
}


void	hit_point(t_minirt *minirt, t_ray ray, t_hit *hit)
{

	hit->position = add_vec3(ray.origin, mult_nb_vec3(ray.direction, hit->dst));
	hit->normal = get_normal(minirt, *hit);
}

t_vec3	get_normal_sphere(t_minirt *minirt, t_hit hit)
{
	t_vec3 normal;
	t_vec3 sphere_in;
	
	normal = normalize_vec3(sub_vec3(hit.position, hit.object.position));
	sphere_in = sub_vec3(minirt->cam.position,hit.object.position);
	if (dot_vec3(sphere_in, sphere_in) <= hit.object.spec.sphere.radius) // test si on est a l'interieur de la sphere
	{
	//	printf("HERE\n");
		normal = mult_nb_vec3(normal, -1.0f); // inversion de la normal si on est a l'interieur de la sphere
	}
	return (normal);
}

t_vec3	get_normal(t_minirt *minirt, t_hit hit)
{
	(void)minirt;
	t_vec3 normal;

	ft_memset(&normal, 0, sizeof(t_vec3));
	if (hit.object.type == SPHERE)
		normal = normalize_vec3(sub_vec3(hit.position, hit.object.position));
		// les autres if a faire
	return (normal);
}



float	calcul_light_ratio(t_minirt *minirt, t_hit hit)
{
	t_vec3 light_dir;
	float light;

	light_dir = normalize_vec3(sub_vec3(hit.position, minirt->light.position)); // calcul de la direction de la lumiere
	light_dir = mult_nb_vec3(light_dir, -1.0f * minirt->light.brightness); // inversion de la direction de la lumiere pour aller de nous a la lumiere et pas le contraire
	light = dot_vec3(hit.normal, light_dir); // calcul de la lumiere, == cos(angle)
	if (light < 0.0f) // on ne veut pas de valeur negative, c'est le plus grand entre 0 et la lumiere
		light = 0.0f;
	return (light);
}

// t_color	get_light_color(t_minirt *minirt)
// {
// 	t_color color;
// 	color = add_colors(minirt->ambient_light.color, minirt->light.color);

// }

t_color	get_color_object_pixel(t_minirt *minirt, t_hit hit)
{
	// t_color color;
	float 	light;

	if (hit.dst == -1)
		return (t_color){0};
	light = calcul_light_ratio(minirt, hit);

//	color = add_colors(minirt->ambient_light.color, minirt->light.color);

	return (multiply_color_float(hit.object.color, light));
}