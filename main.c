#include "minishell.h"

int		ft_runcommand(char *cmd, char *path, char **envp)
{
	int		i;
	char	*exec;
	char	**argv;
	char	**paths;
	char	*ctnt;
	int		status;
	pid_t 	pid;

	paths = ft_split(path, ':');
	argv = ft_split(cmd, ' ');
	exec = argv[0];
	pid = fork();
	if (pid == 0)
	{
		i = 0;
		while (paths[i])
		{
			ctnt = ft_strjoin(paths[i], "/");
			ctnt = ft_strjoin(ctnt, exec);
			execve(ctnt, argv, envp);
			free(ctnt);
			i++;
		}
		exit(0);
	}
	else if (pid > 0)
	{
		wait(&status);
		i = 0;
		while (argv[i])
		{
			free(argv[i]);
			i++;
		}
		free(argv);
	}
	return (0);
}

int		main(int argc, char **argv, char **envp)
{
	char	*path;
	char	*line;
	char 	**instructions;
	int		i;

	i = 0;
	path = 0;
	while (envp[i])
	{
		if (envp[i][0] == 'P' && envp[i][1] == 'A' &&
				envp[i][2] == 'T' && envp[i][3] == 'H' && envp[i][4] == '=')
			path = envp[i] + 5;
		i++;
	}
	if (path == 0)
		printf("Path error\n");
	printf("%s\n", path);
	while (42)
	{
		if (errno == 0)
			write(1, "minishell>> ", 12);
		else
			write(1, "minishell>< " , 12);
		ft_gnl(0, &line);
		instructions = ft_split(line, ';');
		i = 0;
		while (instructions[i])
		{
			ft_runcommand(instructions[i], path, envp);
			free(instructions[i]);
			i++;
		}
		free(instructions);
	}
}
