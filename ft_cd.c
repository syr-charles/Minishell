/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laclide <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/20 13:00:15 by laclide           #+#    #+#             */
/*   Updated: 2020/11/26 15:23:14 by charles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_remove_cell(char **tab, int i)
{
	free(tab[i]);
	while (tab[i + 1])
	{
		tab[i] = tab[i + 1];
		i++;
	}
	tab[i] = 0;
}

void	make_cdpath(char **tab, char *new)
{
	int		i;
	int		j;
	int		k;

	k = 0;
	new[0] = 0;
	if (tab[0] == 0)
		return ;
	i = 0;
	while (tab[i])
	{
		new[k++] = '/';
		j = 0;
		while (tab[i][j])
		{
			new[k] = tab[i][j];
			k++;
			j++;
		}
		free(tab[i]);
		i++;
	}
	free(tab);
	new[k] = 0;

}

char	*true_form_cdpath(char *str)
{
	int		i;
	int		j;
	char	*new;
	char	**tab;

	i = 0;
	j = 0;
	while (str[i])
		i++;
	new = malloc(i + 1);
	tab = ft_split(str, '/');
	i = 0;
	while (tab[i])
	{
		if (tab[i][0] == '.' && tab[i][1] == '\0')
			ft_remove_cell(tab, i);
		else if (i == 0 && tab[i][0] == '.' && tab[i][1] == '.' && tab[i][2] == '\0')
			ft_remove_cell(tab, i);
		else if (i > 0 && tab[i][0] == '.' && tab[i][1] == '.' && tab[i][2] == '\0')
		{
			i--;
			ft_remove_cell(tab, i);
			ft_remove_cell(tab, i);
		}
		else
			i++;
	}
	make_cdpath(tab, new);
	return (new);
}

char	*strctn(char *str1, char inter, char *str2)
{
	char	*new;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (str1[i])
		i++;
	while (str2[j])
		j++;
	if ((new = malloc(sizeof(char) * (i + j + 2))) == NULL)
		return (NULL);
	i = 0;
	j = 0;
	while (str1[i])
	{
		new[i] = str1[i];
		i++;
	}
	if (str1[i - 1] != inter)
	{
		new[i] = inter;
		i++;
	}
	while (str2[j])
	{
		new[i + j] = str2[j];
		j++;
	}
	new[i+j] = '\0';
	return (new);
}

int		cd_no_argv(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (envp[i][0] == 'H' && envp[i][1] == 'O' && envp[i][2] == 'M' &&
				envp[i][3] == 'E' && envp[i][4] == '=')
		{
			if (envp[i][5] != '\0')
			{
				printf("%s\n", envp[i]+5);
				return (chdir(envp[i]+5));
			}
			return (0);
		}
		i++;
	}
	return (1);
}

int		cd_cdpath(char *str, char **envp)
{
	int		i;
	char	*new;

	i = 0;
	while (envp[i])
	{
		if (envp[i][0] == 'C' && envp[i][1] == 'D' && envp[i][2] == 'P' 
			&& envp[i][3] == 'A' && envp[i][4] == 'T' && envp[i][5] == 'H' 
			&& envp[i][6] == '=' && envp[i][7] != '\0')
		{
			new = strctn(envp[i]+7, '/', str);
			if (chdir(new) == 0)
				return (0);
			else
				break;
		}
		i++;
	}
	return (1);
}

char	*cd_pwd(char *str2, char **envp)
{
	char	*new;
	int		i;

	i = 0;
	while (envp[i])
	{
		if (envp[i][0] == 'P' && envp[i][1] == 'W' && envp[i][2] == 'D' 
			&& envp[i][3] == '=' && envp[i][4] != '\0')
		{
			return (new = strctn(envp[i]+4, '/', str2));
		}	
		i++;
	}
	return (NULL);
}

int		ft_cd(char **argv, char **envp)
{
	int		i;
	char	*str;
	char	*new;

	i = 0;
	str = NULL;
	if (argv[0] == NULL)
		return (cd_no_argv(envp));
	if (argv[1][0] != '/')
	{
		if (argv[1][0] != '.')
		{
			if (cd_cdpath(argv[0], envp) == 0)
				return (0);
		}
	}
	if (str == NULL)
		str = cd_pwd(argv[1], envp);
	str = true_form_cdpath(str);	
	if (chdir(str) == 0)
		printf("Do something!\n");
	return (0);
}

