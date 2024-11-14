#include "miniRT.h"
#include <sys/stat.h>
#include <fcntl.h>

void	print_arr(char **arr);
void	ft_free_arr(char **arr);

// int	prasing_map(t_minirt *minirt, char *file) //t_minirt *minirt a passer afin d'initialiser les struct avec les infos de la map
// {
// 	int		map_file;
// 	char	**pars_line;
// 	int		i;
// 	char	**pars_arg;
// 	int		fov_pars;
// 	char	*s;

// 	i = 0;
// 	fov_pars = 0.f;
// 	map_file = open(file, O_RDONLY);
// 	if (map_file == -1)
// 	{
// 		printf("Failed to open the map\n");
// 		return (-1);
// 	}
// 	s = get_next_line(map_file);
// 	while (s != NULL)
// 	{
// 		free(s);
// 		s = get_next_line(map_file);
// 		i++;
// 	}
// 	printf("nb line %d = 6\n", i);
// 	close(map_file);

// 	pars_line = malloc(sizeof(char *) * (i + 1));
// 	if (pars_line == NULL)
// 	{
// 		printf("Malloc filed\n");
// 		return (-1);
// 	}
	
// 	i = 0;
// 	map_file = open(file, O_RDONLY);
// 	if (map_file == -1)
// 	{
// 		printf("Failed to open the map\n");
// 		return (-1);
// 	}
// 	pars_line[i] = get_next_line(map_file);
// 	while (pars_line[i] != NULL)
// 	{
// 		printf("line %d : %s", i, pars_line[i]);
// 		i++;
// 		pars_line[i] = get_next_line(map_file);
// 	}
// 	pars_arg = ft_split(pars_line[1], ' ');
// 	print_arr(pars_arg);
// 	printf("FOV bf atoi: %s\n", pars_arg[3]);
// 	fov_pars = ft_atoi(pars_arg[3]);
// 	minirt->cam.FOV = (float)fov_pars; //normalement fov pars
// 	printf("fov : %f\n", minirt->cam.FOV);
// 	close(map_file);
// 	ft_free_arr(pars_arg);
// 	ft_free_arr(pars_line);
// 	return (0);
// }

int	prasing_map(t_minirt *minirt, char *file)
{
	int		map_file;
	char	*line;

	open(file, O_RDONLY);
	line = get_next_line(map_file);
	while (line)
	{
		pars_line(line, minirt);
		free(line);
		line = get_next_line(map_file);
	}

}


void	print_arr(char **arr)
{
	int	i;

	i = -1;
	while (arr[++i])
		printf("%s\n", arr[i]);
	return ;
}

void	ft_free_arr(char **arr)
{
	int	i;

	i = -1;
	while (arr[++i])
		free(arr[i]);
	free(arr);
}