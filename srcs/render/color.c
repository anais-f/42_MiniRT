#include "miniRT.h"

// Multiplication de la couleur d'un objet par la couleur de la lumière (avec intensité)
t_color multiply_colors(t_color color1, t_color color2)
{
    t_color result;
	float r;
	float g;
	float b;

	r = (color1.r / 255.f) * (color2.r / 255.f);
	g = (color1.g / 255.f) * (color2.g / 255.f);
	b = (color1.b / 255.f) * (color2.b / 255.f);
	result.r = r * 255;
	result.g = g * 255;
	result.b = b * 255;
    return (result);
}

t_color	multiply_color_float(t_color color, float f)
{
	t_color result;

	result.r = color.r * f;
	result.g = color.g * f;
	result.b = color.b * f;
	return (result);
}

t_color add_colors(t_color color1, t_color color2)
{
	t_color result;
	float r;
	float g;
	float b;

	r = (color1.r / 255.f) + (color2.r / 255.f);
	g = (color1.g / 255.f) + (color2.g / 255.f);
	b = (color1.b / 255.f) + (color2.b / 255.f);
	result.r = r * 255;
	result.g = g * 255;
	result.b = b * 255;
	if (result.r > 255)
		result.r = 255;
	if (result.g > 255)
		result.g = 255;
	if (result.b > 255)
		result.b = 255;

	return (result);
}
