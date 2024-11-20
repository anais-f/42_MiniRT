#include "miniRT.h"

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

	result = (t_color){0xFFFFFFFF};
	if (r <= 1)
		result.r = r * 255;
	if (g <= 1)
		result.g = g * 255;
	if (b <= 1)
		result.b = b * 255;

	return (result);
}

t_vec3	color_to_vec3(t_color color)
{
	t_vec3 vec;

	vec.x = (float)color.r / 255.0f;
	vec.y = (float)color.g / 255.0f;
	vec.z = (float)color.b / 255.0f;
	return (vec);
}

t_color	vec3_to_color(t_vec3 vec)
{
	t_color color;

	color = (t_color){0xFFFFFFFF};
	if (vec.x <= 1)
		color.r = vec.x * 255.f;
	if (vec.y <= 1)
	color.g = vec.y * 255.f;
	if (vec.z <= 1)
		color.b = vec.z * 255.f;
	return (color);
}