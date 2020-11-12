/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdana <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 15:34:29 by cdana             #+#    #+#             */
/*   Updated: 2020/11/12 14:24:34 by charles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_blocks(char const *s, char c)
{
	int		i;
	int		blocks;

	if (s == 0)
		return (0);
	i = 0;
	blocks = 1;
	while (s[i])
	{
		if (s[i] == c)
		{
			while (s[i] == c)
				i++;
			blocks++;
		}
		else
			i++;
	}
	return (blocks);
}

void		ft_fill(char *dest, char const *src, int n)
{
	int		i;

	i = 0;
	while (i < n)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = 0;
}

char		**ft_split(char const *s, char c)
{
	char	**out;
	int		i;
	int		j;
	int		k;

	if (s == 0 || (out = malloc(sizeof(char*) * (ft_blocks(s, c) + 1))) == 0)
		return (0);
	k = 0;
	i = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		j = i;
		while (s[j] && s[j] != c)
			j++;
		if ((out[k] = malloc(j - i + 1)) == 0)
			return (0);
		ft_fill(out[k], s + i, j - i);
		if (j > i)
			k++;
		i = j;
	}
	out[k] = 0;
	return (out);
}

char        **ft_strip(char const *s)
{
    char    **out;
    char    flag;
    int     i;
    int     j;
    int     k;

    if (s == 0 || (out = malloc(sizeof(char*) * (ft_blocks(s, ' ') + 1))) == 0)
        return (0);
    k = 0;
    i = 0;
    flag = 0;
    while (s[i])
    {
        while (s[i] == ' ')
            i++;
        if (flag == 0 && (s[i] == 39 || s[i] == 34))
            flag = s[i++];
        j = i;
        while (s[j] && (flag != 0 || s[j] != ' '))
        {
            if (flag != 0 && s[j] == flag)
				break ;
			j++;
        }
        if ((out[k] = malloc(j - i + 1)) == 0)
            return (0);
        ft_fill(out[k], s + i, j - i);
        if (j > i)
            k++;
		i = j;
		if (flag != 0)
		{
			flag = 0;
			i = j + 1;
		}
    }
    out[k] = 0;
    return (out);
}
