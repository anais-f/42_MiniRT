#ifndef VECTOR_H
# define VECTOR_H

# include <stdlib.h>
# include <stdio.h>
# include <mlx.h>
# include <math.h>


typedef struct s_vec2
{
	float	px;
	float	py;
}	t_vec2;

typedef struct s_vec3
{
	float	x;
	float	y;
	float	z;
}	t_vec3;

typedef struct s_vec4
{
	float	x;
	float	y;
	float	z;
	float	a;
}	t_vec4;


t_vec3 add_vec3(t_vec3 a, t_vec3 b);
t_vec3 sub_vec3(t_vec3 a, t_vec3 b);
t_vec3 mult_vec3(t_vec3 a, t_vec3 b);
t_vec3 mult_nb_vec3(t_vec3 a, float nb);
t_vec3 div_vec3(t_vec3 a, t_vec3 b);
t_vec3 div_denom_vec3(t_vec3 a, float nb);
t_vec3 div_num_vec3(t_vec3 a, float nb);
t_vec3	cross_vec3(t_vec3 a, t_vec3 b);
float	dot_vec3(t_vec3 a, t_vec3 b);
float	norm_vec3(t_vec3 a);
t_vec3	normalize_vec3(t_vec3 a);


#endif