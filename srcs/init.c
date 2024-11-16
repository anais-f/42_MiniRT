#include "miniRT.h"

/* A CHANGER DE .C PAR LA SUITE */

int	init_camera(t_minirt *minirt)
{
	minirt->cam.position = (t_vec3){0.f, 0.f, -2.f};
	minirt->cam.direction = (t_vec3){0.f, 0.f, 1.f};
	minirt->cam.FOV = 60 * M_PI / 180;
	minirt->cam.ratio = (float)WIDTH_WIN / (float)HEIGHT_WIN;
	return (0);
}

void	init_color(t_minirt *minirt)
{
	minirt->color.r = 0;
	minirt->color.g = 0;
	minirt->color.b = 0;
	minirt->color.a = 0;
}

int	init_minirt(t_minirt *minirt)
{
	minirt->to_radian = M_PI / 180;
	minirt->to_degree = 180 / M_PI;
	// fonction init camera, image, color, objects etc...
	return (0);
}

int	init_light(t_minirt *minirt)
{
	minirt->light.position = (t_vec3){2.f, 2.f, 0.f};
	minirt->light.brightness = 1.0f; // entre 0 et 1

	//RGB non necessaire dans le mandatory
	minirt->light.color.b = 255;
	minirt->light.color.g = 255;
	minirt->light.color.r = 255;
	minirt->light.color.a = 0;
	return (0);
}

int	init_ambient_light(t_minirt *minirt)
{
	minirt->ambient_light.color.b = 255;
	minirt->ambient_light.color.g = 255;
	minirt->ambient_light.color.r = 255;
	minirt->ambient_light.color.a = 0;
	minirt->ambient_light.brightness = 0.1f;
	return (0);
}

int	init_object(t_minirt *minirt)
{
	minirt->object[0].type = SPHERE;
	minirt->object[0].position = (t_vec3){-1.f, 1.f, 0.f};
	minirt->object[0].direction = (t_vec3){0.f, 0.f, 0.f};
	minirt->object[0].color.b = 85;
	minirt->object[0].color.g = 97;
	minirt->object[0].color.r = 205;
	minirt->object[0].color.a = 0;
	minirt->object[0].spec.sphere.radius = 0.5f;

	minirt->object[1].type = SPHERE;
	minirt->object[1].position = (t_vec3){-0.5f, 1.f, 0.f};
	minirt->object[1].direction = (t_vec3){0.f, 0.f, 0.f};
	minirt->object[1].color.b = 14;
	minirt->object[1].color.g = 65;
	minirt->object[1].color.r = 92;
	minirt->object[1].color.a = 0;
	minirt->object[1].spec.sphere.radius = 0.5f;

	minirt->object[2].type = SPHERE;
	minirt->object[2].position = (t_vec3){0.f, 1.f, 0.f};
	minirt->object[2].direction = (t_vec3){0.f, 0.f, 0.f};
	minirt->object[2].color.b = 172;
	minirt->object[2].color.g = 225;
	minirt->object[2].color.r = 243;
	minirt->object[2].color.a = 0;
	minirt->object[2].spec.sphere.radius = 0.5f;
	return (0);
}
