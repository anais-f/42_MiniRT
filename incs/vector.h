#ifndef VECTOR_H
# define VECTOR_H

# include <stdlib.h>
# include <stdio.h>
# include <math.h>

typedef struct s_vec2
{
	double	x;
	double	y;
}	t_vec2;

typedef struct s_vec3
{
	double	x;
	double	y;
	double	z;
}	t_vec3;

typedef struct s_vec4
{
	double	x;
	double	y;
	double	z;
	double	a;
}	t_vec4;


t_vec3	add_vec3(t_vec3 a, t_vec3 b);
t_vec3	sub_vec3(t_vec3 a, t_vec3 b);
t_vec3	mult_vec3(t_vec3 a, t_vec3 b);
t_vec3	mult_nb_vec3(t_vec3 a, double nb);
t_vec3	div_vec3(t_vec3 a, t_vec3 b);
t_vec3	div_denom_vec3(t_vec3 a, double nb);
t_vec3	div_num_vec3(t_vec3 a, double nb);
t_vec3	cross_vec3(t_vec3 a, t_vec3 b);
double	dot_vec3(t_vec3 a, t_vec3 b);
double	norm_vec3(t_vec3 a);
t_vec3	normalize_vec3(t_vec3 a);
int		compare_norm_vec3(t_vec3 a, t_vec3 b);

#endif