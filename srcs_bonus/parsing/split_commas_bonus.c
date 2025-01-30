/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_commas_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acancel <acancel@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 16:37:46 by acancel           #+#    #+#             */
/*   Updated: 2025/01/29 13:28:12 by acancel          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT_bonus.h"

static size_t	count_commas(char *str, char c);
static char		**fill_array_commas(char const *s, char c, char **arr);

char	**split_commas(char const *s, char c)
{
	size_t	words;
	char	**arr;

	arr = 0;
	if (s == NULL)
		return (NULL);
	words = count_commas((char *)s, c);
	if (words == 0)
		return (NULL);
	arr = ft_calloc(words + 1, sizeof(char *));
	if (!arr)
		return (NULL);
	arr = fill_array_commas((char *)s, c, arr);
	return (arr);
}

static size_t	count_commas(char *str, char c)
{
	size_t	count;
	size_t	i;
	size_t	commas;

	i = 0;
	commas = 0;
	count = 0;
	if (str == NULL)
		return (count);
	while (str[i])
	{
		if (str[i] != c && ((str[i + 1] == c) || str[i + 1] == 0))
			count++;
		if (str[i] == c)
			commas++;
		i++;
	}
	if (commas != 2)
	{
		printf("Error :\nWrong numbers of commas\n");
		return (0);
	}
	return (count);
}

static char	**fill_array_commas(char const *s, char c, char **arr)
{
	size_t	j;
	size_t	start;
	size_t	end;

	start = 0;
	j = 0;
	while (s[start] && j < count_commas((char *)s, c))
	{
		while (s[start] && s[start] == c)
			start++;
		end = start;
		while (s[end] && s[end] != c)
			end++;
		arr[j] = ft_substr((char *)s, start, end - start);
		if (!arr[j])
		{
			ft_free_arr(arr);
			return (NULL);
		}
		start = end;
		j++;
	}
	return (arr);
}
