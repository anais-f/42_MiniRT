/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anfichet <anfichet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 16:12:06 by anfichet          #+#    #+#             */
/*   Updated: 2024/12/14 20:42:05 by anfichet         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_H
# define VECTOR_H

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

typedef struct s_matrix
{
	float	mat[3][3];
}	t_mat;

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
double	dot_vec2(t_vec2 a, t_vec2 b);
double	norm_vec2(t_vec2 a);
t_vec2	normalize_vec2(t_vec2 a);
t_vec3	mult_vec3_matrix(t_vec3 a, t_mat b);
double	distance_vec3(t_vec3 a, t_vec3 b);
t_mat	matrix_identity(void);
t_mat	reverse_identity_matrix(void);
t_mat	multiply_matrix(t_mat a, t_mat b);
t_mat	add_mat(t_mat m1, t_mat m2);
t_mat	mult_float_matrix(float a, t_mat b);

#endif