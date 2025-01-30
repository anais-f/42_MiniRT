/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_error_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acancel <acancel@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 16:37:55 by acancel           #+#    #+#             */
/*   Updated: 2025/01/29 13:28:29 by acancel          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT_bonus.h"

void	ft_free_exit(t_minirt *minirt, char *line, \
						char **line_parsed, int exit_code)
{
	if (line)
		free(line);
	if (line_parsed)
		ft_free_arr(line_parsed);
	if (exit_code)
	{
		array_free(&minirt->objects);
		mlx_destroy_all(&minirt->img);
		exit(exit_code);
	}
}
