#include "minishell.h"

int		ft_echo(char **argv)
{
	int		i;
	int		j;
	int		flag;

	flag = 0;
	i = 1;
	while (argv[i] && argv[i][0] == '-' && argv[i][1] == 'n' && argv[i][2] == '\0')
	{
		flag = 1;
		i++;
	}
	while (argv[i])
	{
		j = 0;
		while (argv[i][j])
			j++;
		write(1, argv[i], j);
		if (argv[i + 1])
			write(1, " ", 1);
		i++;
	}
	if (flag == 0)
		write(1, "\n", 1);
	return (1);
}
