/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_gnl.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdana <cdana@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/07 10:07:42 by cdana             #+#    #+#             */
/*   Updated: 2020/10/06 09:59:52 by cdana            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	slen(char *s, char p)
{
	int		i;

	if (!s)
		return (0);
	i = 0;
	while (s[i] && s[i] != p)
		i++;
	return (i);
}

static int	ft_merge(char **dest, char *right)
{
	int		i;
	int		j;
	char	*out;

	if (!(out = malloc(slen(*dest, '\0') + slen(right, '\0') + 1)))
		return (-1);
	i = 0;
	while ((*dest)[i])
	{
		out[i] = (*dest)[i];
		i++;
	}
	j = 0;
	while (right[j])
	{
		out[i + j] = right[j];
		j++;
	}
	out[i + j] = 0;
	free(*dest);
	*dest = out;
	return (1);
}

static int	ft_read(int fd, char **ctnt)
{
	int		ret;
	char	*buff;

	if (!(buff = malloc(BUFFER_SIZE + 1)))
		return (-1);
	ret = 0;
	while (ctnt[fd][slen(ctnt[fd], '\n')] != '\n'
		&& (ret = read(fd, buff, BUFFER_SIZE)) > 0)
	{
		buff[ret] = 0;
		if (ft_merge(ctnt + fd, buff) == -1)
		{
			free(buff);
			return (-1);
		}
	}
	free(buff);
	if (ret < 0)
		return (-1);
	return (1);
}

static int	ft_cpy_shift(char **ctnt, char **line)
{
	int		i;
	int		j;
	int		ret;

	if (!(*line = malloc(slen(*ctnt, '\n') + 1)))
		return (-1);
	i = 0;
	while ((*ctnt)[i] && (*ctnt)[i] != '\n')
	{
		(*line)[i] = (*ctnt)[i];
		i++;
	}
	(*line)[i] = 0;
	ret = ((*ctnt)[i] == '\n');
	if ((*ctnt)[i] == '\n')
		i++;
	j = 0;
	while ((*ctnt)[i + j])
	{
		(*ctnt)[j] = (*ctnt)[i + j];
		j++;
	}
	(*ctnt)[j] = 0;
	return (ret);
}

int			ft_gnl(int fd, char **line)
{
	static char		*ctnt[OPEN_MAX];
	int				ret;

	if (fd < 0 || !line || fd > OPEN_MAX || BUFFER_SIZE <= 0)
		return (-1);
	if (ctnt[fd] == NULL)
	{
		if (!(ctnt[fd] = malloc(1)))
			return (-1);
		ctnt[fd][0] = '\0';
	}
	if (ft_read(fd, ctnt) == -1)
		return (-1);
	if ((ret = ft_cpy_shift(ctnt + fd, line)) == 0)
	{
		free(ctnt[fd]);
		ctnt[fd] = NULL;
	}
	return (ret);
}
