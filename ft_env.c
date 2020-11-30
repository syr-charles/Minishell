#include "minishell.h"

char	*ft_get_env(t_env *e, char *s)
{
	int		i;
	int		j;

	i = 0;
	while (e->envp[i])
	{
		j = 0;
		while (s[j] && e->envp[i][j] == s[j])
			j++;
		if (s[j] == 0 && e->envp[i][j] == '=')
			return (e->envp[i] + j + 1);
		i++;
	}
	return (NULL);
}

void	ft_del_env(t_env *e, char *name)
{
	int		i;
	int		j;

	i = 0;
	while (e->envp[i])
	{
		j = 0;
		while (name[j] && e->envp[i][j] == name[j])
			j++;
		if (name[j] == 0 && e->envp[i][j] == '=')
		{
			free(e->envp[i]);
			j = i;
			while (e->envp[j + 1])
			{
				e->envp[j] = e->envp[j + 1];
				j++;
			}
			e->envp[j] = 0;
		}
		else
			i++;
	}
}

void	ft_set_env(t_env *e, char *name, char *ctnt)
{
	char	**new_env;
	int		i;
	int		j;
	int 	check;

	check = 0;
	i = 0;
	while (e->envp[i])
		i++;
	new_env = malloc((i + 2) * sizeof(char*));
	i = 0;
	while (e->envp[i])
	{
		j = 0;
		while (name[j] && name[j] == e->envp[i][j])
			j++;
		if (name[j] == 0 && e->envp[i][j] == '=')
		{
			//free(e->envp[i]);
			new_env[i] = ft_strjoin(name, ctnt);
			check = 1;
		}
		else
			new_env[i] = e->envp[i];
		i++;
	}
	if (check == 0) 
		new_env[i++] = ft_strjoin(name, ctnt);
	new_env[i] = 0;
	//free(e->envp);
	e->envp = new_env;
}
