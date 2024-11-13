#include "miniRT.h"

#include <sys/stat.h>
#include <fcntl.h>

void	print_tab(char **arr);
void	ft_free_tab(char **arr);

int	prasing_map(char *file) //t_minirt *minirt a passer afin d'initialiser les struct avec les infos de la map
{
	int		map_file;
	char	*pars_line[6];
	int		i;
	char	**pars_arg;
	// int		fov_pars;

	i = 0;
	map_file = open(file, O_RDONLY);
	if (map_file == -1)
	{
		printf("Failed to open the map\n");
		return (-1);
	}
	while (i <= 5) // 5 car 5 lignes JE GALERE SUR LA CONDITION
	{
		pars_line[i] = get_next_line(map_file);
		printf("line %d : %s", i, pars_line[i]);
		i++;
	}
	pars_arg = ft_split(pars_line[1], ' ');
	print_tab(pars_arg);
	// fov_pars = ft_atoi(pars_arg[0]);
	// minirt->cam.FOV = 0; //normalement fov pars
	close(map_file);
	ft_free_tab(pars_arg);
	// ft_free_tab(pars_line);
	return (0);
}

void	print_tab(char **arr)
{
	int	i;

	i = -1;
	while (arr[++i])
		printf("%s\n", arr[i]);
	return ;
}

void	ft_free_tab(char **arr)
{
	int	i;

	i = -1;
	while (arr[++i])
		free(arr[i]);
	free(arr);
}