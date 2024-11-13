#include "miniRT.h"

int	check_argv(int argc, char *str)
{
	const char	str_check[] = ".rt";
	size_t		i;
	size_t		len_str;

	if (argc != 2)
	{
		printf("Invalid number of arguments\n");
		return (1);
	}
	i = 0;
	len_str = ft_strlen(str);
	if (len_str < 4)
	{
		printf("Invalid parameter\n");
		return (1);
	}
	if (ft_strncmp(str_check, &str[len_str - 3], 4) != 0)
	{
		printf("Invalid file\n");
		return (1);
	}
	return (0);
}
