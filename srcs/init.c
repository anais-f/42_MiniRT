#include "miniRT.h"

/* A CHANGER DE .C PAR LA SUITE */

int	init_camera(t_minirt *minirt)
{
	minirt->cam.position = (t_vec3){0.f, 0.f, 0.f};
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
	minirt->light.position = (t_vec3){2.f, 2.f, 2.f};
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
	minirt->object.type = SPHERE;
	minirt->object.position = (t_vec3){0.f, 0.f, 0.f};
	minirt->object.direction = (t_vec3){0.f, 0.f, 0.f};
	minirt->object.color.b = 255;
	minirt->object.color.g = 0;
	minirt->object.color.r = 255;
	minirt->object.color.a = 0;
	minirt->object.spec.sphere.radius = 1.0f;
	return (0);
}