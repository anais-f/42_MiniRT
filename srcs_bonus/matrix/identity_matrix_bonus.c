/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   identity_matrix_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acancel <acancel@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 16:13:15 by anfichet          #+#    #+#             */
/*   Updated: 2025/01/29 13:27:12 by acancel          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "vector_bonus.h"

t_mat	matrix_identity(void)
{
	t_mat	mat;

	mat.mat[0][0] = 1;
	mat.mat[0][1] = 0;
	mat.mat[0][2] = 0;
	mat.mat[1][0] = 0;
	mat.mat[1][1] = 1;
	mat.mat[1][2] = 0;
	mat.mat[2][0] = 0;
	mat.mat[2][1] = 0;
	mat.mat[2][2] = 1;
	return (mat);
}

t_mat	reverse_identity_matrix(void)
{
	t_mat	mat;

	mat.mat[0][0] = -1;
	mat.mat[0][1] = 0;
	mat.mat[0][2] = 0;
	mat.mat[1][0] = 0;
	mat.mat[1][1] = 1;
	mat.mat[1][2] = 0;
	mat.mat[2][0] = 0;
	mat.mat[2][1] = 0;
	mat.mat[2][2] = -1;
	return (mat);
}
