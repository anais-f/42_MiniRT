#ifndef COLOR_H
# define COLOR_H

typedef union u_color
{
	__uint32_t	color;
	struct
	{
		__uint8_t	b;
		__uint8_t	g;
		__uint8_t	r;
		__uint8_t	a;
	};
}	t_color;

/* BGR is because with a computer we print white pixel on black screen,
in real life we use RGB because we print black color on white paper */

t_vec3	color_to_vec3(t_color color);
t_color	vec3_to_color(t_vec3 vec);


#endif