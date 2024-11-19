#include "miniRT.h"

// Multiplication de la couleur d'un objet par la couleur de la lumière (avec intensité)
t_color multiply_colors(t_color color, t_color ambient_color)
{
    t_color result;
	float r;
	float g;
	float b;

	r = (color.r / 255.f) * (ambient_color.r / 255.f);
	g = (color.g / 255.f) * (ambient_color.g / 255.f);
	b = (color.b / 255.f) * (ambient_color.b / 255.f);
	result.r = r * 255;
	result.g = g * 255;
	result.b = b * 255;
    return (result);
}

t_color add_colors(t_color ambient, t_color light)
{
	t_color result;
	float r;
	float g;
	float b;

	r = (ambient.r / 255.f) + (light.r / 255.f);
	g = (ambient.g / 255.f) + (light.g / 255.f);
	b = (ambient.b / 255.f) + (light.b / 255.f);
	result.r = r * 255;
	result.g = g * 255;
	result.b = b * 255;
	return (result);
}