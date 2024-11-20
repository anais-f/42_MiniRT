#include "miniRT.h"

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