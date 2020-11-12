#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <limits.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# define BUFFER_SIZE 100
# include <errno.h>

int		ft_gnl(int fd, char **line);
char	**ft_split(char const *line, char sep);
char	**ft_strip(char const *line, char **envp);
char	*ft_strjoin(char const *left, char const *right);
int		ft_echo(char **argv);
#endif
