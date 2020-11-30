#include "minishell.h"

int		ft_basecommand(char **argv, t_env *e)
{
	if (argv[0] == 0)
		return 1;
	if (argv[0][0] == 'e' && argv[0][1] == 'x'
			&& argv[0][2] == 'i' && argv[0][3] == 't'
			&& argv[0][4] == '\0')
	{
		write(1, "exit\n", 5);
		exit(errno);
	}
	if (argv[0][0] == 'e' && argv[0][1] == 'c'
			&& argv[0][2] == 'h' && argv[0][3] == 'o'
			&& argv[0][4] == '\0')
	{
		ft_echo(argv);
		return (1);
	}
	if (argv[0][0] == 'c' && argv[0][1] == 'd'
			&& argv[0][2] == '\0')
	{
		ft_cd(argv, e);
		return (1);
	}
	return (0);
}


int		ft_runcommand(char *cmd, char *path, t_env *e)
{
	int		i;
	char	*exec;
	char	**argv;
	char	**paths;
	char	*ctnt;
	int		status;
	pid_t 	pid;

	paths = ft_split(path, ':');
	argv = ft_strip(cmd, e);
	exec = argv[0];
	if (ft_basecommand(argv, e) == 1)
		return (1);
	pid = fork();
	if (pid == 0)
	{
		i = 0;
		execve(exec, argv, e->envp);
		while (paths[i])
		{
			ctnt = ft_strjoin(paths[i], "/");
			ctnt = ft_strjoin(ctnt, exec);
			execve(ctnt, argv, e->envp);
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
	t_env	e;
	char	*path;
	char	*line;
	char 	**instructions;
	int		i;

	e.envp = envp;
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
			ft_runcommand(instructions[i], path, &e);
			free(instructions[i]);
			i++;
		}
		free(instructions);
	}
}
