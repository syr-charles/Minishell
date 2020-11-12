#include "minishell.h"

char	**ft_tabappend(char **tab, char *line)
{
	char	**ntab;
	int		i;

	if (tab == 0 || line == 0)
	{
		tab = malloc(sizeof(char*));
		tab[0] = 0;
		return (tab);
	}
	if (line[0] == 0)
	{
		free(line);
		return (tab);
	}
	i = 0;
	while (tab[i])
		i++;
	ntab = malloc((i + 2) * sizeof(char*));
	i = 0;
	while (tab[i])
	{
		ntab[i] = tab[i];
		i++;
	}
	ntab[i] = line;
	ntab[i + 1] = 0;
	free(tab);
	return (ntab);
}

char	*ft_lineappend(char *line, char c)
{
	char	*nline;
	int		i;

	if (line == 0)
	{
		line = malloc(sizeof(char));
		line[0] = 0;
		return (line);
	}
	i = 0;
	while (line[i])
		i++;
	nline = malloc((i + 2) * sizeof(char));
	i = 0;
	while (line[i])
	{
		nline[i] = line[i];
		i++;
	}
	nline[i] = c;
	nline[i + 1] = 0;
	free(line);
	return (nline);
}

char	*ft_completeline(char *line, char **envp, char const *s, int *i)
{
	int		a;
	int		b;
	int		c;
	char 	*env;

	(*i)++;
	env = ft_lineappend(0,0);
	while (s[*i] && s[*i] != ' ' && s[*i] != '\'' && s[*i] != '\"' && s[*i] != '$')
	{
		env = ft_lineappend(env, s[*i]);
		(*i)++;
	}
	a = 0;
	while (envp[a])
	{
		b = 0;
		while (env[b] && envp[a][b] && envp[a][b] == env[b])
			b++;
		if (env[b] == 0 && envp[a][b] == '=')
			break ;
		a++;
	}
	free(env);
	if (envp[a] == 0)
		return (line);
	b++;
	while (envp[a][b])
	{
		line = ft_lineappend(line, envp[a][b]);
		b++;
	}
	return (line);
}

char 	**ft_strip(char const *s, char **envp)
{
	char 	**tab;
	char	*line;
	int		i;
	char	flag;
	
	i = 0;
	tab = ft_tabappend(0, 0);
	line = ft_lineappend(0, 0);
	flag = 0;
	while (s[i])
	{
		if (s[i] == '$')
			line = ft_completeline(line, envp, s, &i);
		else if (flag == 0 && (s[i] == '\'' || s[i] == '\"'))
			flag = s[i++];
		else if (flag != 0 && s[i] == flag)
		{
			flag = 0;
			i++;
		}
		else if (s[i] && (flag != 0 || s[i] != ' '))
			line = ft_lineappend(line, s[i++]);
		else if (flag == 0 && s[i] == ' ')
		{
			while (s[i] && s[i] == ' ')
				i++;
			tab = ft_tabappend(tab, line);
			line = ft_lineappend(0, 0);
		}
	}
	tab = ft_tabappend(tab, line);
	return (tab);
}
