/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   float_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acancel <acancel@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 16:37:21 by acancel           #+#    #+#             */
/*   Updated: 2025/01/29 13:27:55 by acancel          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT_bonus.h"

bool	is_valid_float(char *str_float)
{
	int		i;
	bool	comma;

	i = 0;
	comma = false;
	if (str_float[i] == '+' || str_float[i] == '-')
		i++;
	while ((str_float[i] >= '0' && str_float[i] <= '9') || str_float[i] == '.')
	{
		if (str_float[i] == '.')
		{
			if (comma == true)
			{
				printf("Error :\nWrong float format %s\n", str_float);
				return (false);
			}
			comma = true;
		}
		i++;
	}
	if (i != (int)ft_strlen(str_float))
		return (printf("Error :\nWrong float format %s\n", str_float), false);
	return (true);
}

int	check_overflow(const char *str, size_t *i, int sign, float *nb)
{
	if ((((int)(*nb)*10 + str[*i] - '0') / 10) != (int)(*nb))
	{
		errno = ERANGE;
		if (sign < 0)
			(*nb) = ((float)INT_MIN);
		(*nb) = ((float)INT_MAX);
		return (-1);
	}
	(*nb) = (*nb) * 10 + str[(*i)++] - '0';
	return (0);
}

float	ft_atof(const char *str)
{
	size_t	i;
	float	nb_bf_comma;
	float	nb_af_comma;
	int		sign;

	i = 0;
	nb_bf_comma = 0.f;
	nb_af_comma = 0.0f;
	sign = 1;
	if (str[i] == '-')
		sign = -sign;
	if (str[i] == '+' || str[i] == '-')
		i++;
	while ((str[i] >= '0' && str[i] <= '9'))
	{
		if (check_overflow(str, &i, sign, &nb_bf_comma) == -1)
			return (nb_bf_comma);
	}
	if (str[i] == '.')
	{
		i = ft_strlen(str) - 1;
		while ((str[i] >= '0' && str[i] <= '9'))
			nb_af_comma = nb_af_comma / 10 + str[i--] - '0';
	}
	return ((nb_bf_comma + nb_af_comma / 10) * sign);
}
